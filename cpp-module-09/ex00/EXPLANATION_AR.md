================================================================================
                    شرح تفصيلي لبرنامج Bitcoin Exchange
                    (البيتكوين إكسينج - صرف العملات الرقمية)
================================================================================

📋 ملخص البرنامج:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
البرنامج يقوم بتحويل قيمة البيتكوين من تاريخ معين إلى عملة أخرى باستخدام
أسعار الصرف التاريخية. يحتوي على معالجة شاملة للأخطاء والتحقق من صحة البيانات.

================================================================================
📁 البنية الأساسية للملفات:
================================================================================

1️⃣  BitcoinExchange.hpp (ملف الرأس - التعريفات)
2️⃣  BitcoinExchange.cpp (الملف التطبيقي - التنفيذ)
3️⃣  main.cpp (الدالة الرئيسية)
4️⃣  data.csv (ملف البيانات التاريخية)
5️⃣  Makefile (ملف البناء)

================================================================================
🔍 شرح ملف BitcoinExchange.hpp (الرأس)
================================================================================

    #ifndef BITCOINEXCHANGE_HPP      ← حماية من الشمول المزدوج
    #define BITCOINEXCHANGE_HPP

    #include <map>                   ← مكتبة الخريطة (المفتاح، القيمة)
    #include <iostream>              ← المدخلات والمخرجات
    #include <string>                ← نوع البيانات string

    class BitcoinExchange              ← تعريف الفئة الرئيسية
    {
        public:                        ← الأعضاء العامة (الدوال)
        
            BitcoinExchange();         ← المُنشِّئ (Constructor)
                                       ينشئ كائن جديد من الفئة
            
            BitcoinExchange(const BitcoinExchange& copy);
                                       ← منشِّئ النسخ (Copy Constructor)
                                       ينسخ كائن موجود
            
            BitcoinExchange& operator=(const BitcoinExchange& other);
                                       ← عامل الإسناد (Assignment Operator)
                                       ينسخ القيم من كائن إلى آخر
            
            ~BitcoinExchange();        ← المُدمِّر (Destructor)
                                       يحرر الموارد عند حذف الكائن
            
            void processFile(const std::string& fileName);
                                       ← الدالة الرئيسية لمعالجة الملف

        private:                       ← الأعضاء الخاصة (البيانات الداخلية)
        
            std::map<std::string, double> rates;
                                       ← خريطة تخزن التاريخ والسعر
                                       المفتاح: التاريخ (string)
                                       القيمة: سعر الصرف (double)
            
            void loadData();           ← دالة لتحميل بيانات CSV
            
            bool isValidDate(const std::string& date) const;
                                       ← التحقق من صحة صيغة التاريخ
            
            bool isValideValue(const std::string& value) const;
                                       ← التحقق من صحة القيمة (0-1000)
            
            double getRateForDate(const std::string& date) const;
                                       ← الحصول على سعر الصرف
    };

================================================================================
🔍 شرح ملف BitcoinExchange.cpp (التطبيق)
================================================================================

▶ المُنشِّئ الافتراضي:
─────────────────────────────────────────────────────────────────────────────
    BitcoinExchange::BitcoinExchange() 
    {
        loadData();    ← استدعاء دالة تحميل البيانات تلقائياً
    }

    الغرض: عندما ننشئ كائن جديد، يتم تحميل بيانات الأسعار من CSV مباشرة

▶ منشِّئ النسخ:
─────────────────────────────────────────────────────────────────────────────
    BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) 
        : rates(copy.rates)    ← نسخ قائمة الأسعار من الكائن الأصلي
    {
    }

    الغرض: السماح بنسخ كامل البيانات من كائن إلى آخر

▶ عامل الإسناد:
─────────────────────────────────────────────────────────────────────────────
    BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
    {
        if (this != &other)        ← التحقق من عدم إسناد الكائن لنفسه
        {
            rates = other.rates;   ← نسخ البيانات
        }
        return (*this);            ← إرجاع المرجع للسماح بالإسناد المتسلسل
    }

    الغرض: تعيين قيم كائن إلى آخر بأمان

▶ المُدمِّر:
─────────────────────────────────────────────────────────────────────────────
    BitcoinExchange::~BitcoinExchange()
    {
        // لا نحتاج لحذف شيء يدويًا لأن الخريطة تحرر نفسها تلقائياً
    }

    الغرض: تنظيف الموارد (لا يلزم هنا لأن STL يتولى ذلك)

▶ دالة تحميل البيانات (تفصيلي جداً):
─────────────────────────────────────────────────────────────────────────────
    void BitcoinExchange::loadData()
    {
        std::ifstream file("data.csv");     ← فتح ملف البيانات
        
        if (!file.is_open())                ← فحص الفتح الناجح
        {
            std::cerr << "Error: Cannot open data.csv" << std::endl;
            return;                         ← الخروج عند الفشل
        }
        
        std::string line;                   ← متغير لقراءة السطر
        std::getline(file, line);           ← تخطي السطر الأول (عناوين الأعمدة)
        
        while (std::getline(file, line))    ← قراءة كل سطر من الملف
        {
            std::istringstream iss(line);   ← تحليل السطر
            
            std::string date;               ← متغير للتاريخ
            std::string rateStr;            ← متغير لسعر النص
            
            if (std::getline(iss, date, ',') && std::getline(iss, rateStr))
                                            ← استخراج القيم حتى الفاصلة
            {
                double rate = std::strtod(rateStr.c_str(), NULL);
                                            ← تحويل السعر من نص إلى رقم
                
                rates[date] = rate;         ← إضافة إلى الخريطة
            }
        }
        
        file.close();                       ← إغلاق الملف
    }

    مثال على البيانات المحملة:
    ┌──────────────┬──────────┐
    │     date     │  rate    │
    ├──────────────┼──────────┤
    │ 2009-01-02   │    0     │
    │ 2009-01-05   │    0.5   │
    │ 2011-06-15   │   24.88  │
    └──────────────┴──────────┘

▶ دالة التحقق من صحة التاريخ:
─────────────────────────────────────────────────────────────────────────────
    bool BitcoinExchange::isValidDate(const std::string& date) const
    {
        if (date.length() != 10)            ← التحقق من الطول (YYYY-MM-DD = 10)
            return (false);
        
        if (date[4] != '-' || date[7] != '-')  ← التحقق من موقع الفواصل
            return (false);
        
        for (int i = 0; i < 10; i++)        ← حلقة فحص كل حرف
        {
            if (i == 4 || i == 7)           ← تخطي الفواصل
                continue;
            
            if (!std::isdigit(date[i]))     ← التحقق من أن القيمة رقمية
                return (false);
        }
        
        int year = std::strtol(date.substr(0, 4).c_str(), NULL, 10);
        int month = std::strtol(date.substr(5, 2).c_str(), NULL, 10);
        int day = std::strtol(date.substr(8, 2).c_str(), NULL, 10);
                                            ← استخراج ومعالجة الأرقام
        
        // فحوصات المنطقية:
        if (year < 2009 || year > 2024)     ← السنة معقولة
            return (false);
        if (month < 1 || month > 12)        ← الشهر صحيح
            return (false);
        if (day < 1 || day > 31)            ← اليوم في النطاق
            return (false);
        
        return (true);                      ← كل شيء صحيح
    }

▶ دالة التحقق من صحة القيمة:
─────────────────────────────────────────────────────────────────────────────
    bool BitcoinExchange::isValideValue(const std::string& value) const
    {
        char *endptr;                       ← مؤشر للموضع الذي توقف التحويل
        double num = std::strtod(value.c_str(), &endptr);
                                            ← تحويل النص إلى رقم
        
        if (*endptr != '\0')                ← التحقق من عدم وجود أحرف زائدة
            return (false);
        
        if (num < 0)                        ← التحقق من أن الرقم موجب
            return (false);
        
        if (num > 1000)                     ← التحقق من الحد الأقصى
            return (false);
        
        return (true);                      ← كل شيء صحيح
    }

▶ دالة الحصول على السعر لتاريخ معين:
─────────────────────────────────────────────────────────────────────────────
    double BitcoinExchange::getRateForDate(const std::string& date) const
    {
        std::map<std::string, double>::const_iterator it;
                                            ← إنشاء مؤشر للخريطة
        
        it = rates.find(date);              ← البحث عن التاريخ المطلوب بدقة
        
        if (it != rates.end())              ← إذا وجد بالضبط
            return (it->second);            ← إرجاع السعر مباشرة
        
        it = rates.lower_bound(date);       ← البحث عن أول تاريخ >= المطلوب
        
        if (it == rates.begin())            ← إذا لا يوجد تاريخ سابق
            return (-1);                    ← إرجاع خطأ
        
        --it;                               ← الذهاب للتاريخ السابق
        
        return (it->second);                ← إرجاع سعره (التقريب للأسفل)
    }

    التسلسل المنطقي:
    1. البحث عن التاريخ بدقة → إن وجد، إرجاع السعر
    2. البحث عن التاريخ اللاحق → ثم الانتقال للسابق
    3. إن لم يوجد سابق → خطأ
    4. وإلا → إرجاع السعر

▶ دالة معالجة ملف الإدخال (الأكثر تعقيداً):
─────────────────────────────────────────────────────────────────────────────
    void BitcoinExchange::processFile(const std::string& fileName)
    {
        std::ifstream file(fileName.c_str());   ← فتح ملف الإدخال
        
        if (!file.is_open())                    ← فحص الفتح
        {
            std::cerr << "Error: could not open file." << std::endl;
            return;
        }
        
        std::string line;
        std::getline(file, line);               ← تخطي السطر الأول
        
        while (std::getline(file, line))        ← قراءة كل سطر من الإدخال
        {
            size_t divPos = line.find(" | ");   ← البحث عن الفاصل
            
            if (divPos == std::string::npos)    ← إذا لم توجد الفاصل
            {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;                       ← تخطي هذا السطر
            }
            
            std::string date = line.substr(0, divPos);      ← استخراج التاريخ
            std::string value = line.substr(divPos + 3);    ← استخراج القيمة
            
            // حذف المسافات الزائدة:
            date.erase(0, date.find_first_not_of(" \t"));
            date.erase(date.find_last_not_of(" \t") + 1);
            
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            
            // فحوصات الصحة:
            if (!isValidDate(date))             ← فحص التاريخ
            {
                std::cerr << "Error: invalid input => " << date << std::endl;
                continue;
            }
            
            if (!isValideValue(value))          ← فحص القيمة
            {
                char *endptr;
                double num = std::strtod(value.c_str(), &endptr);
                
                if (num < 0)
                    std::cerr << "Error: not a positive number." << std::endl;
                else if (num > 1000)
                    std::cerr << "Error: too large a number." << std::endl;
                else
                    std::cerr << "Error: invalid input => " << value << std::endl;
                
                continue;
            }
            
            double rate = getRateForDate(date);  ← الحصول على السعر
            
            if (rate == -1)                     ← فحص وجود البيانات
            {
                std::cerr << "Error: no rate found for date => " << date << std::endl;
                continue;
            }
            
            double amount = std::strtod(value.c_str(), NULL);  ← تحويل القيمة
            double result = amount * rate;      ← حساب النتيجة
            
            // طباعة النتيجة بصيغة منسقة:
            std::cout << date << " => " << std::fixed 
                      << std::setprecision(2)    ← 2 منزلة عشرية
                      << amount << " = " << result << std::endl;
        }
        
        file.close();                           ← إغلاق الملف
    }

================================================================================
📝 شرح ملف main.cpp (الدالة الرئيسية)
================================================================================

    int main(int argc, char *argv[])
    {
        ↑ argc: عدد المعاملات (اسم البرنامج + اسم الملف)
        ↑ argv: مصفوفة المعاملات النصية
        
        if (argc != 2)          ← نتوقع: برنامج + ملف (مجموع 2)
        {
            std::cerr << "Usage: ./btc <input_file>" << std::endl;
            return (1);         ← إرجاع كود خطأ
        }
        
        BitcoinExchange exchange;   ← إنشاء كائن (تحميل البيانات تلقائياً)
        
        exchange.processFile(argv[1]);  ← معالجة الملف المعطى
                                        (argv[1] = المعامل الأول بعد البرنامج)
        
        return (0);             ← نهاية ناجحة
    }

================================================================================
📊 تسلسل تنفيذ البرنامج
================================================================================

    1. تشغيل البرنامج:
       $ ./btc input.txt
       
    2. التنفيذ:
       ┌─────────────────────────────────────────────────────────┐
       │ main() → BitcoinExchange() → loadData()                 │
       │                              (تحميل data.csv)           │
       │                                                          │
       │ processFile("input.txt")                                │
       │ ├─ قراءة السطر الأول (رؤوس الأعمدة)                    │
       │ └─ لكل سطر:                                            │
       │    ├─ استخراج التاريخ والقيمة                         │
       │    ├─ فحص الصحة                                       │
       │    ├─ البحث عن السعر                                   │
       │    └─ طباعة النتيجة أو الخطأ                          │
       └─────────────────────────────────────────────────────────┘

================================================================================
🧪 مثال عملي خطوة بخطوة
================================================================================

المدخل: input.txt يحتوي على:
    date | value
    2011-06-15 | 0.5

التنفيذ:

    1. قراءة السطر: "2011-06-15 | 0.5"
    
    2. استخراج:
       date = "2011-06-15"
       value = "0.5"
    
    3. فحص التاريخ: ✓ صحيح
    
    4. فحص القيمة: ✓ موجب وأقل من 1000
    
    5. البحث عن السعر:
       - البحث عن "2011-06-15" بدقة → قد لا يوجد
       - البحث عن أول تاريخ >= 2011-06-15 → مثلاً "2011-06-20"
       - الرجوع للتاريخ السابق "2011-06-15" أو أقبله
       - السعر = 24.88
    
    6. الحسابة:
       0.5 × 24.88 = 12.44
    
    7. الطباعة:
       2011-06-15 => 0.50 = 12.44

================================================================================
⚙️  Makefile شرح
================================================================================

    NAME = btc                          ← اسم البرنامج الملموم
    CXX = c++                           ← المترجم
    CXXFLAGS = -Wall -Wextra -Werror   ← أعلام التحذيرات الصارمة
    SRCS = main.cpp BitcoinExchange.cpp ← الملفات المصدرية
    OBJS = $(SRCS:.cpp=.o)             ← تحويل إلى .o
    
    all: $(NAME)                        ← الهدف الافتراضي: بناء البرنامج
    
    $(NAME): $(OBJS)                    ← بناء البرنامج من الكائنات
        $(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
    
    %.o: %.cpp                         ← قاعدة تجميع عامة
        $(CXX) $(CXXFLAGS) -c $< -o $@
    
    clean: rm -f $(OBJS)               ← حذف الملفات المؤقتة
    fclean: clean  rm -f $(NAME)       ← حذف كل شيء
    re: fclean all                     ← إعادة بناء كاملة

================================================================================
✨ المميزات الرئيسية للكود
================================================================================

1. ✓ معالجة الأخطاء الشاملة:
   - فحص وجود الملفات
   - التحقق من صيغة البيانات
   - رسائل خطأ واضحة

2. ✓ البيانات الفعالة:
   - استخدام std::map للبحث السريع O(log n)
   - lower_bound للبحث عن أقرب تاريخ

3. ✓ التوافق:
   - C++98 (بدون C++11 features مثل auto)
   - معايير صارمة (-Wall -Wextra -Werror)

4. ✓ التصميم النظيف:
   - فصل المسؤوليات (فئة واحدة، وظائف واضحة)
   - دوال خاصة للعمليات الداخلية

================================================================================
