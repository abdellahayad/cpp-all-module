#include "PmergeMe.hpp"

// ==================== Canonical ====================

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& copy) : vec(copy.vec), lst(copy.lst) {}
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) { vec = other.vec; lst = other.lst; }
    return *this;
}

// ==================== Parse ====================

static bool isNumber(const char *str) {
    if (!str || str[0] == '\0') return false;
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i])) return false;
    return true;
}

void PmergeMe::parsInput(int ac, char **av) {
    if (ac < 2) throw std::runtime_error("Error!");
    for (int i = 1; i < ac; i++) {
        if (!isNumber(av[i])) throw std::runtime_error("Error!");
        long num = strtol(av[i], NULL, 10);
        if (num <= 0 || num > INT_MAX) throw std::runtime_error("Error!");
        if (std::find(vec.begin(), vec.end(), (int)num) != vec.end())
            throw std::runtime_error("Error: duplicate!");
        vec.push_back((int)num);
        lst.push_back((int)num);
    }
}

// ==================== Jacobsthal ====================
// 1, 1, 3, 5, 11, 21, 43...
// نستخدمه لتحديد ترتيب إدخال الخاسرين

std::vector<int> PmergeMe::jacobsthalSeq(int n) {
    std::vector<int> jac;
    jac.push_back(0);
    jac.push_back(1);
    while (true) {
        int next = jac[jac.size()-1] + 2 * jac[jac.size()-2];
        jac.push_back(next);
        if (next >= n) break;
    }
    return jac;
}

// ================================================================
//  VECTOR IMPLEMENTATION
//  C = vector< vector<int> >
//  كل عنصر داخلي هو "group": front()=الفائز، الباقي=الخاسرون
// ================================================================

void PmergeMe::fordJohnsonVec(std::vector<std::vector<int> >& C) {
    if ((int)C.size() <= 1) return;

    bool has_leftover = (C.size() % 2 != 0);
    std::vector<int> leftover;
    if (has_leftover) {
        leftover = C.back();
        C.pop_back();
    }

    std::vector<std::vector<int> > next_level;
    for (int i = 0; i < (int)C.size(); i += 2) {
        std::vector<int>& A = C[i];
        std::vector<int>& B = C[i + 1];
        if (A.front() < B.front()) std::swap(A, B);
        for (int j = 0; j < (int)B.size(); j++)
            A.push_back(B[j]);
        next_level.push_back(A);
    }
    C = next_level;

    fordJohnsonVec(C);

    int pair_size = (int)C.front().size() / 2;

    std::vector<std::vector<int> > main_chain; // الفائزون
    std::vector<std::vector<int> > pend_chain; // الخاسرون

    for (int i = 0; i < (int)C.size(); i++) {
        std::vector<int> winner(C[i].begin(), C[i].begin() + pair_size);
        std::vector<int> loser (C[i].begin() + pair_size, C[i].end());
        main_chain.push_back(winner);
        pend_chain.push_back(loser);
    }

    main_chain.insert(main_chain.begin(), pend_chain[0]);

    std::vector<int> jac = jacobsthalSeq((int)pend_chain.size());

    int prev = 1;
    for (int k = 2; k < (int)jac.size(); k++) {
        int next = jac[k];
        if (next > (int)pend_chain.size())
            next = (int)pend_chain.size();

        for (int idx = next - 1; idx >= prev; idx--) {
            int val = pend_chain[idx].front();

            int winner_pos = -1;
            for (int w = 0; w < (int)main_chain.size(); w++) {
                if (main_chain[w].front() == C[idx].front()) {
                    winner_pos = w;
                    break;
                }
            }
            int lo = 0, hi = (winner_pos >= 0) ? winner_pos : (int)main_chain.size();
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (main_chain[mid].front() < val) lo = mid + 1;
                else hi = mid;
            }
            main_chain.insert(main_chain.begin() + lo, pend_chain[idx]);
        }
        prev = next;
    }

    if (has_leftover) {
        int val = leftover.front();
        int lo = 0, hi = (int)main_chain.size();
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (main_chain[mid].front() < val) lo = mid + 1;
            else hi = mid;
        }
        main_chain.insert(main_chain.begin() + lo, leftover);
    }

    C = main_chain;
}

std::vector<int> PmergeMe::sortVec() {
    // حوّل vec إلى vector< vector<int> >
    std::vector<std::vector<int> > C;
    for (int i = 0; i < (int)vec.size(); i++) {
        std::vector<int> g;
        g.push_back(vec[i]);
        C.push_back(g);
    }
    fordJohnsonVec(C);
    // استخرج النتيجة
    std::vector<int> result;
    for (int i = 0; i < (int)C.size(); i++)
        result.push_back(C[i].front());
    return result;
}

// ================================================================
//  LIST IMPLEMENTATION
//  نفس المنطق لكن بـ list< list<int> >
// ================================================================

void PmergeMe::fordJohnsonLst(std::list<std::list<int> >& C) {
    if ((int)C.size() <= 1) return;

    bool has_leftover = (C.size() % 2 != 0);
    std::list<int> leftover;
    if (has_leftover) {
        leftover = C.back();
        C.pop_back();
    }

    // ① أزواج
    std::list<std::list<int> > next_level;
    std::list<std::list<int> >::iterator it = C.begin();
    while (it != C.end()) {
        std::list<int>& A = *it; ++it;
        std::list<int>& B = *it; ++it;
        if (A.front() < B.front()) std::swap(A, B);
        // الحق B داخل A
        for (std::list<int>::iterator j = B.begin(); j != B.end(); ++j)
            A.push_back(*j);
        next_level.push_back(A);
    }
    C = next_level;

    // ② recursive
    fordJohnsonLst(C);

    // ③ فصل winner/loser
    int pair_size = (int)C.front().size() / 2;

    std::list<std::list<int> > main_chain;
    std::list<std::list<int> > pend_chain;

    for (std::list<std::list<int> >::iterator i = C.begin(); i != C.end(); ++i) {
        std::list<int>::iterator split = i->begin();
        std::advance(split, pair_size);
        std::list<int> winner(i->begin(), split);
        std::list<int> loser (split, i->end());
        main_chain.push_back(winner);
        pend_chain.push_back(loser);
    }

    // ④ b1 في البداية
    main_chain.insert(main_chain.begin(), pend_chain.front());

    // ⑤ Jacobsthal insertion
    std::vector<int> jac = jacobsthalSeq((int)pend_chain.size());

    // حوّل pend_chain و C إلى vector مؤقت للوصول بـ index
    std::vector<std::list<int> > pend_v(pend_chain.begin(), pend_chain.end());
    std::vector<std::list<int> > C_v(C.begin(), C.end());

    int prev = 1;
    for (int k = 2; k < (int)jac.size(); k++) {
        int next = jac[k];
        if (next > (int)pend_v.size()) next = (int)pend_v.size();

        for (int idx = next - 1; idx >= prev; idx--) {
            int val = pend_v[idx].front();

            // ابحث حتى موضع winner المقابل
            int winner_pos = -1;
            int w = 0;
            for (std::list<std::list<int> >::iterator it2 = main_chain.begin();
                 it2 != main_chain.end(); ++it2, ++w) {
                if (it2->front() == C_v[idx].front()) {
                    winner_pos = w;
                    break;
                }
            }
            int hi = (winner_pos >= 0) ? winner_pos : (int)main_chain.size();

            // linear search (list لا تدعم binary search مباشرة)
            std::list<std::list<int> >::iterator pos = main_chain.begin();
            int count = 0;
            while (pos != main_chain.end() && count < hi && pos->front() < val) {
                ++pos; ++count;
            }
            main_chain.insert(pos, pend_v[idx]);
        }
        prev = next;
    }

    // ⑥ leftover
    if (has_leftover) {
        int val = leftover.front();
        std::list<std::list<int> >::iterator pos = main_chain.begin();
        while (pos != main_chain.end() && pos->front() < val)
            ++pos;
        main_chain.insert(pos, leftover);
    }

    C = main_chain;
}

std::list<int> PmergeMe::sortLst() {
    std::list<std::list<int> > C;
    for (std::list<int>::iterator i = lst.begin(); i != lst.end(); ++i) {
        std::list<int> g;
        g.push_back(*i);
        C.push_back(g);
    }
    fordJohnsonLst(C);
    std::list<int> result;
    for (std::list<std::list<int> >::iterator i = C.begin(); i != C.end(); ++i)
        result.push_back(i->front());
    return result;
}

// ================================================================
//  RUN
// ================================================================

void PmergeMe::run() {
    // قبل
    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    // Vector
    clock_t s1 = clock();
    std::vector<int> resVec = sortVec();
    clock_t e1 = clock();
    double t1 = (double)(e1 - s1) / CLOCKS_PER_SEC * 1e6;

    // List
    clock_t s2 = clock();
    std::list<int> resLst = sortLst();
    clock_t e2 = clock();
    double t2 = (double)(e2 - s2) / CLOCKS_PER_SEC * 1e6;

    // بعد
    std::cout << "After:  ";
    for (size_t i = 0; i < resVec.size(); i++)
        std::cout << resVec[i] << " ";
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << resVec.size()
              << " elements with std::vector : " << t1 << " us" << std::endl;
    std::cout << "Time to process a range of " << resLst.size()
              << " elements with std::list   : " << t2 << " us" << std::endl;
}