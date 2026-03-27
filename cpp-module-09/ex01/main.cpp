#include "RPN.hpp"
#include <iostream>

// ====================== الدالة الرئيسية ======================
int main(int argc, char *argv[])
{
    // التحقق من عدد المعاملات
    // يجب أن يكون: اسم البرنامج + التعبير (المجموع = 2)
    if (argc != 2)
    {
        // إذا كان العدد مختلفاً، طباعة رسالة الاستخدام
        std::cerr << "Usage: ./RPN <RPN_expression>" << std::endl;
        // إرجاع كود خطأ
        return (1);
    }

    try
    {
        // إنشاء كائن من فئة RPN
        RPN rpn;
        
        // حساب التعبير المعطى
        // argv[1] هو المعامل الأول (التعبير)
        int result = rpn.calculate(argv[1]);
        
        // طباعة النتيجة
        std::cout << result << std::endl;
        
        // إرجاع 0 للإشارة إلى النجاح
        return (0);
    }
    // التقاط أي استثناء يُطرح
    catch (const std::exception& e)
    {
        // طباعة رسالة الخطأ على stderr
        std::cerr << e.what() << std::endl;
        // إرجاع كود خطأ
        return (1);
    }
}
