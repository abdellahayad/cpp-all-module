#include "BitcoinExchange.hpp"
#include <fstream>      // لقراءة الملفات
#include <sstream>      // لتحليل السلاسل النصية
#include <iomanip>      // للتنسيق (دقة الأرقام العشرية)
#include <cstdlib>      // لمعالجة الأخطاء
#include <algorithm>    // للعمليات على الحاويات
#include <cctype>       // لفحص أنواع الأحرف

// ====================== المُنشئ الافتراضي ======================
BitcoinExchange::BitcoinExchange() 
{
    // استدعاء الدالة الخاصة لتحميل البيانات من ملف CSV
    loadData();
}

// ====================== منشئ النسخ ======================
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) 
    : rates(copy.rates)  // نسخ خريطة الأسعار من الكائن الأصلي
{
}

// ====================== عامل الإسناد ======================
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    // التحقق من عدم إسناد الكائن لنفسه (تجنب الحذف المزدوج)
    if (this != &other)
    {
        // نسخ خريطة الأسعار من الكائن الآخر
        rates = other.rates;
    }
    // إرجاع المؤشر الحالي للسماح بالإسناد المتسلسل
    return (*this);
}

// ====================== المُدمّر ======================
BitcoinExchange::~BitcoinExchange()
{
    // يتم تنظيف الموارد تلقائياً (الخريطة تحررها الذاكرة تلقائياً)
}

// ====================== دالة تحميل البيانات ======================
void BitcoinExchange::loadData()
{
    // فتح ملف البيانات التاريخي (data.csv)
    std::ifstream file("data.csv");
    
    // التحقق من نجاح فتح الملف
    if (!file.is_open())
    {
        // إذا فشل الفتح، طباعة رسالة خطأ وإرجاع
        std::cerr << "Error: Cannot open data.csv" << std::endl;
        return;
    }
    
    // متغير لتخزين السطر الكامل من الملف
    std::string line;
    
    // قراءة السطر الأول (رؤساء الأعمدة: date,exchange_rate)
    std::getline(file, line);
    
    // حلقة لقراءة جميع أسطر البيانات
    while (std::getline(file, line))
    {
        // فتح بث نصي للسطر الحالي لتحليله
        std::istringstream iss(line);
        
        // متغير لتخزين التاريخ (قبل الفاصلة)
        std::string date;
        
        // متغير لتخزين السعر (بعد الفاصلة)
        std::string rateStr;
        
        // استخراج التاريخ حتى الفاصلة
        if (std::getline(iss, date, ',') && std::getline(iss, rateStr))
        {
            // تحويل السعر من نص إلى رقم عشري مزدوج (double)
            double rate = std::strtod(rateStr.c_str(), NULL);
            
            // إضافة التاريخ والسعر إلى الخريطة
            rates[date] = rate;
        }
    }
    
    // إغلاق ملف البيانات
    file.close();
}

// ====================== دالة التحقق من صحة التاريخ ======================
bool BitcoinExchange::isValidDate(const std::string& date) const
{
    // التحقق من أن طول التاريخ 10 أحرف (YYYY-MM-DD)
    if (date.length() != 10)
        return (false);
    
    // التحقق من أن هناك فواصل في الموضع الصحيح
    if (date[4] != '-' || date[7] != '-')
        return (false);
    
    // حلقة للتحقق من أن باقي الأحرف أرقام
    for (int i = 0; i < 10; i++)
    {
        // تخطي الفواصل
        if (i == 4 || i == 7)
            continue;
        // التحقق من أن القيمة رقمية
        if (!std::isdigit(date[i]))
            return (false);
    }
    
    // استخراج السنة والشهر واليوم كأرقام
    int year = std::strtol(date.substr(0, 4).c_str(), NULL, 10);
    int month = std::strtol(date.substr(5, 2).c_str(), NULL, 10);
    int day = std::strtol(date.substr(8, 2).c_str(), NULL, 10);
    
    // التحقق من أن السنة معقولة
    if (year < 2009 || year > 2024)
        return (false);
    
    // التحقق من أن الشهر بين 1 و 12
    if (month < 1 || month > 12)
        return (false);
    
    // التحقق من أن اليوم بين 1 و 31
    if (day < 1 || day > 31)
        return (false);
    
    // إذا اجتازت جميع الفحوصات، التاريخ صحيح
    return (true);
}

// ====================== دالة التحقق من صحة القيمة ======================
bool BitcoinExchange::isValideValue(const std::string& value) const
{
    // محاولة تحويل النص إلى رقم عشري
    char *endptr;  // مؤشر للموضع الذي توقف عنده التحويل
    double num = std::strtod(value.c_str(), &endptr);
    
    // التحقق من عدم وجود أحرف إضافية بعد الرقم
    if (*endptr != '\0')
        return (false);
    
    // التحقق من أن الرقم ليس سالباً
    if (num < 0)
        return (false);
    
    // التحقق من أن الرقم لا يتجاوز 1000
    if (num > 1000)
        return (false);
    
    // إذا اجتازت جميع الفحوصات، القيمة صحيحة
    return (true);
}

// ====================== دالة الحصول على السعر لتاريخ معين ======================
double BitcoinExchange::getRateForDate(const std::string& date) const
{
    // إنشاء مؤشر (iterator) للبحث في الخريطة (النوع الصريح بدلاً من auto)
    std::map<std::string, double>::const_iterator it;
    
    // البحث عن التاريخ المطلوب بدقة في الخريطة
    it = rates.find(date);
    
    // إذا وجد التاريخ بدقة، إرجاع السعر
    if (it != rates.end())
        return (it->second);
    
    // إذا لم يوجد بدقة، البحث عن أقرب تاريخ سابق
    it = rates.lower_bound(date);
    
    // إذا كان المؤشر في البداية، لا توجد تواريخ سابقة
    if (it == rates.begin())
        return (-1);  // إرجاع -1 للإشارة إلى وجود خطأ
    
    // الانتقال إلى التاريخ السابق
    --it;
    
    // إرجاع السعر للتاريخ السابق الأقرب
    return (it->second);
}

// ====================== دالة معالجة ملف الإدخال ======================
void BitcoinExchange::processFile(const std::string& fileName)
{
    // محاولة فتح ملف الإدخال
    std::ifstream file(fileName.c_str());
    
    // التحقق من نجاح فتح الملف
    if (!file.is_open())
    {
        // إذا فشل، طباعة رسالة خطأ
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    
    // متغير لتخزين السطر الكامل من الملف
    std::string line;
    
    // قراءة السطر الأول (رؤساس الأعمدة)
    std::getline(file, line);
    
    // حلقة لمعالجة جميع أسطر الإدخال
    while (std::getline(file, line))
    {
        // البحث عن موضع الفاصل (|) في السطر
        size_t divPos = line.find(" | ");
        
        // إذا لم توجد الفاصل، طباعة رسالة خطأ
        if (divPos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;  // الانتقال إلى السطر التالي
        }
        
        // استخراج التاريخ (قبل الفاصل)
        std::string date = line.substr(0, divPos);
        
        // استخراج القيمة (بعد الفاصل)
        std::string value = line.substr(divPos + 3);
        
        // حذف المسافات الزائدة من التاريخ (البادئة والنهاية)
        date.erase(0, date.find_first_not_of(" \t"));
        date.erase(date.find_last_not_of(" \t") + 1);
        
        // حذف المسافات الزائدة من القيمة
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        
        // التحقق من صحة التاريخ
        if (!isValidDate(date))
        {
            std::cerr << "Error: invalid input => " << date << std::endl;
            continue;  // الانتقال إلى السطر التالي
        }
        
        // التحقق من صحة القيمة
        if (!isValideValue(value))
        {
            // تحويل القيمة إلى رقم لفحص سبب الخطأ
            char *endptr;
            double num = std::strtod(value.c_str(), &endptr);
            
            // إذا كانت القيمة سالبة
            if (num < 0)
                std::cerr << "Error: not a positive number." << std::endl;
            // إذا كانت القيمة كبيرة جداً
            else if (num > 1000)
                std::cerr << "Error: too large a number." << std::endl;
            // حالات أخرى
            else
                std::cerr << "Error: invalid input => " << value << std::endl;
            
            continue;  // الانتقال إلى السطر التالي
        }
        
        // الحصول على سعر الصرف للتاريخ المطلوب
        double rate = getRateForDate(date);
        
        // إذا كان السعر -1، لا توجد بيانات للتاريخ
        if (rate == -1)
        {
            std::cerr << "Error: no rate found for date => " << date << std::endl;
            continue;
        }
        
        // تحويل القيمة من نص إلى رقم عشري
        double amount = std::strtod(value.c_str(), NULL);
        
        // حساب النتيجة (المبلغ × سعر الصرف)
        double result = amount * rate;
        
        // طباعة النتيجة بصيغة مرتبة
        std::cout << date << " => " << std::fixed << std::setprecision(2) 
                  << amount << " = " << result << std::endl;
    }
    
    // إغلاق ملف الإدخال
    file.close();
}