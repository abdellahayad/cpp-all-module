#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <string>

// فئة تقوم بتبادل العملات الرقمية (بيتكوين)
class BitcoinExchange
{
    public:
        // المُنشئ الافتراضي - ينشئ كائن جديد
        BitcoinExchange();
        
        // منشئ النسخ - ينسخ كائن موجود
        BitcoinExchange(const BitcoinExchange& copy);
        
        // عامل الإسناد - ينسخ قيم كائن إلى آخر
        BitcoinExchange& operator=(const BitcoinExchange& other);
        
        // المُدمّر - يحرر الموارد عند حذف الكائن
        ~BitcoinExchange();

        // الدالة العامة لمعالجة ملف الإدخال
        void processFile(const std::string& fileName);

    private:
        // خريطة لتخزين أسعار البيتكوين (التاريخ -> السعر)
        std::map<std::string, double> rates;
        
        // دالة خاصة لتحميل بيانات الأسعار من ملف CSV
        void loadData();
        
        // دالة للتحقق من صحة التاريخ (صيغة: YYYY-MM-DD)
        bool isValidDate(const std::string& date) const;
        
        // دالة للتحقق من صحة القيمة (رقم بين 0 و 1000)
        bool isValideValue(const std::string& value) const;
        
        // دالة للحصول على سعر الصرف لتاريخ معين
        double getRateForDate(const std::string& date) const;
};

#endif