#include "RPN.hpp"
#include <cstdlib>  // لـ strtod

// ====================== المُنشِّئ الافتراضي ======================
RPN::RPN()
{
    // لا نحتاج لشيء محدد - الـ deque ينشأ فارغاً تلقائياً
}

// ====================== منشِّئ النسخ ======================
RPN::RPN(const RPN& copy)
    : stack(copy.stack)  // نسخ الـ stack من الكائن الأصلي
{
}

// ====================== عامل الإسناد ======================
RPN& RPN::operator=(const RPN& other)
{
    // التحقق من عدم إسناد الكائن لنفسه
    if (this != &other)
    {
        // نسخ الـ stack
        stack = other.stack;
    }
    return (*this);
}

// ====================== المُدمِّر ======================
RPN::~RPN()
{
    // لا نحتاج لتنظيف يدوي - الـ deque يحرر نفسه تلقائياً
}

// ====================== فحص إذا كان النص رقماً ======================
bool RPN::isNumber(const std::string& token) const
{
    // إذا كان الرمز فارغاً، فهو ليس رقماً
    if (token.empty())
        return (false);
    
    // التحقق من أن جميع الأحرف أرقام
    for (size_t i = 0; i < token.length(); i++)
    {
        // إذا كان الحرف ليس رقم، ليس رقم صحيح
        if (!std::isdigit(token[i]))
            return (false);
    }
    
    // إذا مرت جميع الفحوصات، فهو رقم
    return (true);
}

// ====================== فحص إذا كان النص عاملاً حسابياً ======================
bool RPN::isOperator(const std::string& token) const
{
    // العاملات المدعومة: +, -, *, /
    // يجب أن يكون الرمز بطول واحد فقط
    if (token.length() != 1)
        return (false);
    
    // الحرف الوحيد
    char c = token[0];
    
    // التحقق من كونه أحد العاملات
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// ====================== تطبيق العملية الحسابية ======================
double RPN::applyOperation(double a, double b, char op) const
{
    // حسب العامل، نطبق العملية
    switch (op)
    {
        case '+':
            // الجمع: a + b
            return (a + b);
        
        case '-':
            // الطرح: a - b
            return (a - b);
        
        case '*':
            // الضرب: a * b
            return (a * b);
        
        case '/':
            // القسمة: a / b
            // لاحظ: يجب ألا يكون b صفر
            if (b == 0)
            {
                // إذا كان b = 0، خطأ
                throw std::runtime_error("Error: division by zero");
            }
            return (a / b);
        
        default:
            // عامل غير معروف (لا يجب أن يحدث هنا)
            throw std::runtime_error("Error: unknown operator");
    }
}

// ====================== حساب التعبير الرياضي ======================
int RPN::calculate(const std::string& expression)
{
    // تفريغ الـ stack من أي بيانات سابقة
    stack.clear();
    
    // فتح بث نصي لتحليل التعبير
    std::istringstream iss(expression);
    
    // متغير لتخزين كل رمز (token)
    std::string token;
    
    // حلقة قراءة كل رمز من التعبير
    while (iss >> token)
    {
        // فحص إذا كان الرمز رقماً
        if (isNumber(token))
        {
            // تحويل النص إلى رقم واضافته إلى الـ stack
            double number = strtod(token.c_str(), NULL);
            stack.push_back(number);
        }
        // فحص إذا كان الرمز عاملاً
        else if (isOperator(token))
        {
            // التحقق من أن لدينا على الأقل عددين في الـ stack
            if (stack.size() < 2)
            {
                // إذا كان أقل من عددين، خطأ
                throw std::runtime_error("Error: insufficient operands");
            }
            
            // إخراج الرقم الثاني (b) من الـ stack
            double b = stack.back();
            stack.pop_back();
            
            // إخراج الرقم الأول (a) من الـ stack
            double a = stack.back();
            stack.pop_back();
            
            // تطبيق العملية: a op b
            double result = applyOperation(a, b, token[0]);
            
            // إعادة النتيجة إلى الـ stack
            stack.push_back(result);
        }
        else
        {
            // رمز غير معروف (ليس رقم وليس عامل)
            throw std::runtime_error("Error: invalid token");
        }
    }
    
    // التحقق من أن الـ stack يحتوي على رقم واحد فقط (النتيجة النهائية)
    if (stack.size() != 1)
    {
        // إذا كان أكثر من رقم واحد، خطأ
        throw std::runtime_error("Error: invalid expression");
    }
    
    // إرجاع النتيجة النهائية (النقص من الـ double إلى int)
    return (static_cast<int>(stack.back()));
}
