#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <deque>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

class RPN
{
    public:
        RPN();
        
        RPN(const RPN& copy);
        
        RPN& operator=(const RPN& other);
        
        ~RPN();
        
        // دالة حساب التعبير الرياضي
        // المعامل: تعبير بصيغة RPN (مثال: "8 9 * 9 - 9 - 9 - 4 - 1 +")
        int calculate(const std::string& expression);
        
    private:
        // الحاوية الرئيسية: deque (قائمة مزدوجة الطرفين) تعمل كـ stack
        // في هذا التمرين، سنستخدمها كـ stack (عمليات من الطرف الخلفي فقط)
        std::deque<double> stack;
        
        // دالة للتحقق من كون الرقم صحيحاً (رقم صحيح موجب)
        bool isNumber(const std::string& token) const;
        
        // دالة للتحقق من كون الحرف عاملاً حسابياً
        bool isOperator(const std::string& token) const;
        
        // دالة تطبيق العملية الحسابية
        // تأخذ عددين والعامل، وترجع النتيجة
        double applyOperation(double a, double b, char op) const;
};

#endif
