# اسم البرنامج النهائي
NAME = btc

# المترجم المستخدم
CXX = c++

# أعلام المترجم (تحسينات + تحذيرات صارمة)
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# الملفات المصدرية (.cpp)
SRCS = main.cpp BitcoinExchange.cpp

# ملفات الكائنات المترجمة (.o)
OBJS = $(SRCS:.cpp=.o)

# القاعدة الافتراضية: بناء البرنامج النهائي
all: $(NAME)

# قاعدة لبناء البرنامج النهائي من ملفات الكائنات
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# قاعدة للمترجم: تحويل .cpp إلى .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# قاعدة للتنظيف (حذف ملفات الكائنات)
clean:
	rm -f $(OBJS)

# قاعدة التنظيف الكامل (حذف الكائنات والبرنامج)
fclean: clean
	rm -f $(NAME)

# قاعدة لإعادة البناء (تنظيف كامل ثم بناء جديد)
re: fclean all

# إعلام make بأن هذه الأهداف وهمية (ليست ملفات حقيقية)
.PHONY: all clean fclean re
