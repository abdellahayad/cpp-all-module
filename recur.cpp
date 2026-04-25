#include <iostream>
#include <vector>
#include <algorithm>

class PmergeMe {
public:
    // دالة مساعدة لطباعة المصفوفة
    void printVec(const std::vector<int>& v) {
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
    }

    std::vector<int> sortVector(std::vector<int>& v, int level = 0) {
        // مسافة جمالية لتوضيح العمق في الطباعة
        std::string indent(level * 4, ' ');

        if (v.size() <= 1) {
            std::cout << indent << "Reached Base Case: " << v[0] << " (Level " << level << ")\n";
            return v;
        }

        std::cout << indent << ">>> Level " << level << ": Dividing " << v.size() << " elements...\n";

        // 1. تكوين الأزواج (القسم الأول من الكود)
        std::vector<std::pair<int, int> > pairs;
        bool hasLeft = (v.size() % 2 != 0);
        for (size_t i = 0; i < v.size() - (hasLeft ? 1 : 0); i += 2) {
            if (v[i] > v[i+1]) pairs.push_back(std::make_pair(v[i], v[i+1]));
            else pairs.push_back(std::make_pair(v[i+1], v[i]));
        }
        
        std::vector<int> winners;
        for (size_t i = 0; i < pairs.size(); i++) winners.push_back(pairs[i].first);

        std::cout << indent << "Level " << level << " Winners: ";
        printVec(winners);

        // --- السطر السحري: هنا يتجمد الصندوق الحالي وينتظر ---
        std::cout << indent << "!!! Level " << level << " is now FREEZING and calling Level " << level + 1 << "\n";
        
        std::vector<int> mainChain = sortVector(winners, level + 1);

        // --- هنا "يستيقظ" الكود بعد انتهاء الـ Recursion ---
        std::cout << indent << "### Level " << level << " is WAKING UP! MainChain received: ";
        printVec(mainChain);

        // 2. معالجة الخاسرين و Jacobsthal (القسم الثاني من الكود)
        std::vector<int> pend;
        for (size_t i = 0; i < mainChain.size(); i++) {
            for (size_t j = 0; j < pairs.size(); j++) {
                if (mainChain[i] == pairs[j].first) {
                    pend.push_back(pairs[j].second);
                    break;
                }
            }
        }

        std::vector<int> result = mainChain;
        result.insert(result.begin(), pend[0]); // b1 يدخل دائماً أولاً

        std::cout << indent << "Level " << level << " inserting losers (Jacobsthal/Binary Search)...\n";
        
        // تبسيط الإدخال للفهم (التركيز على المفهوم)
        for (size_t i = 1; i < pend.size(); i++) {
            result.insert(std::lower_bound(result.begin(), result.end(), pend[i]), pend[i]);
        }

        if (hasLeft) {
            int leftover = v.back();
            result.insert(std::lower_bound(result.begin(), result.end(), leftover), leftover);
        }

        std::cout << indent << "<<< Level " << level << " FINISHED. Result: ";
        printVec(result);

        return result;
    }
};

int main() {
    PmergeMe solver;
    int arr[] = {16, 1, 15, 2, 14, 3, 13, 4}; // مثال بـ 8 أرقام للتوضيح
    std::vector<int> v(arr, arr + 8);

    std::cout << "Starting Ford-Johnson Algorithm...\n\n";
    solver.sortVector(v);
    
    return 0;
}