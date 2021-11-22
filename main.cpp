#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointer"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "performance-inefficient-string-concatenation"

#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int n;

// Функции для упрощения ввода и вывода в консоль

/**
 * Устанавливает цвет текста в консоли. Фон по умолчанию чёрный.
 * @param text_color ID цвета.
 * 6 - жёлтый
 * 7 - белый
 * 11 - светло-голубой
 */
void set_color(int text_color) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Console descriptor
    SetConsoleTextAttribute(hStdOut, (WORD) (text_color));
}


/**
 * Пока пользователь не введёт значение в корректном
 * диапазоне, функция будет его опрашивать.
 * @param min минимальное значение вводимого элемента;
 * @param max максимальное значение вводимого элемента;
 * @param k ссылка на переменную, куда происходит ввод.
 */
static void input(int min, int max, int &k) {
    k = max + 1;
    do {
        set_color(6);
        printf("> ");
        set_color(7);
        scanf("%d", &k);
    } while (k > max || k < min);
}


/**
 * Функция выводит в консоль входные параметры и
 * ожидаемый результат в будущих тестах.
 * @param expected_result ожидаемый результат;
 * @param args аргументы.
 */
static void print_before_test(const string &expected_result, const char *args) {
    set_color(11);
    printf("Входные параметры: ");
    set_color(7);
    printf("%s", args);
    set_color(11);
    printf("\nОжидаемый результат: ");
    set_color(7);
    printf("%s", expected_result.c_str());
    set_color(11);
    printf("\nРезультаты тестов: \n");
    set_color(7);
}


/**
 * Функция ставит выполнение программы на паузу до того,
 * как пользователь нажмёт на "Enter".
 */
static void enter_to_continue() {
    set_color(6);
    if (!kbhit())
        getch();
}


/**
 * Функция для получения подстроки из строки.
 * @param string исходная строка;
 * @param position начиная с какой строки;
 * @param length сколько символов;
 * @return подстроку.
 */
static char *substr(const char *string, int position, int length) {
    char *result;
    int c;

    if (length > 0)
        result = new char[length + 1];
    else
        result = new char[1];

    for (c = 0; c < length; c++)
        *(result + c) = *((string + position) + c);

    *(result + c) = '\0';

    return result;
}


// Функции, реализующие различные алгоритмы.

/**
 * Четыре функции, по-разному реализующие алгоритм
 * нахождения размера строки.
 * @param s исходная строка;
 * @return размер строки.
 */

static size_t strlen1(const char *s) {
    size_t result = 0;
    while (*s++) result++;
    return result;
}

static size_t strlen2(const char *s) {
    size_t result;
    for (result = 0; *s; s++, result++);
    return result;
}

static size_t strlen3(const char *s) {
    const char *s_begin = s;
    while (*s++);
    return (size_t) (s - s_begin - 1);
}

static size_t strlen4(const char *s) {
    return (size_t) (strchr(s, 0) - s) / sizeof(char);
}


/**
 * Пять функций, по-разному реализующие алгоритм
 * сравнения строк. Одна из функций является отправной
 * точкой для рекурсыы (strcmp3)
 * @param s1 первая строка;
 * @param s2 вторая строка;
 * @return 1, если s1 > s2; -1, если s2 > s1; иначе 0
 */

static int strcmp1(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*s1 - *s2) > 0 ? 1 : (*s1 - *s2) < 0 ? -1 : 0;
}

static int strcmp2(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2))
        s1++, s2++;

    return (*s1 > *s2) - (*s2 > *s1);
}

static int strcmp3_logic(const char *s1, const char *s2) {
    return (*s1 && (*s1 == *s2)) ? strcmp3_logic(s1 + 1, s2 + 1) : *s1 - *s2;
}

static int strcmp3(const char *s1, const char *s2) {
    int temp = strcmp3_logic(s1, s2);
    return temp > 0 ? 1 : temp < 0 ? -1 : 0;
}

static int strcmp4(const char *s1, const char *s2) {
    for (int i = 0;; i++) {
        if (s1[i] != s2[i])
            return s1[i] < s2[i] ? -1 : 1;

        if (s1[i] == '\0')
            return 0;
    }
}


/**
 * Четыре функции, реализующие алгоритм копирования
 * одной строки в другую. К сожалению, с минимальными
 * отличиями.
 * @param dest куда копировать;
 * @param src что копировать.
 */

static void strcpy1(char *dest, const char *src) {
    while ((*dest++ = *src++));
}

static void strcpy2(char *dest, const char *src) {
    int i;
    for (i = 0; i < strlen(src); i++)
        dest[i] = src[i];
    dest[i] = '\0';
}

static void strcpy3(char *dest, const char *src) {
    do
        *dest++ = *src;
    while (*src++);
}

static void strcpy4(char *dest, const char *src) {
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
}


/**
 * Четыре функции, реализующие алгоритм копирования
 * одной подстроки определённой длины в другую строку
 * на определённую позицию.
 * @param dest куда сохранять результат;
 * @param src куда вставлять;
 * @param sub что вставлять;
 * @param k на какую позицию вставлять;
 * @param p сколько вставлять.
 */

static void strins1(char *dest, const char *src, const char *sub, int k) {
    strcpy(dest, "");
    int sub_pos = 0, src_pos = 0, dest_pos = 0, src_length, sub_length;

    src_length = strlen(src);
    sub_length = strlen(sub);

    if (k < 0)
        sub_length = abs(k);

    for (; src_pos < k; src_pos++, dest_pos++) {
        dest[dest_pos] = src[src_pos];

        if (src[src_pos] == '\0')
            break;
    }

    for (; sub_pos < sub_length; dest_pos++, sub_pos++) {
        dest[dest_pos] = sub[sub_pos];

        if (sub[sub_pos] == '\0')
            break;
    }

    for (; src_pos < src_length; src_pos++) {
        dest[dest_pos++] = src[src_pos];

        if (src[src_pos] == '\0')
            break;
    }

    dest[dest_pos] = '\0';
}

static void strins2(char *dest, const char *src, const char *sub, int k) {
    strcpy(dest, "");
    int sub_pos = 0, src_pos = 0, dest_pos = 0, src_length, sub_length;

    src_length = strlen(src);
    sub_length = strlen(sub);

    if (k < 0)
        sub_length = abs(k);

    while (src_pos < k) {
        dest[dest_pos] = src[src_pos];

        if (src[src_pos] == '\0')
            break;

        src_pos++, dest_pos++;
    }

    while (sub_pos < sub_length) {
        dest[dest_pos] = sub[sub_pos];

        if (sub[sub_pos] == '\0')
            break;

        dest_pos++, sub_pos++;
    }

    while (src_pos < src_length) {
        dest[dest_pos++] = src[src_pos];

        if (src[src_pos] == '\0')
            break;

        src_pos++;
    }

    dest[dest_pos] = '\0';
}

static void strins3(char *dest, const char *src, const char *sub, int k) {
    char *before_substring, *after_substring, *cropped_substring;
    int src_length, sub_length;

    strcpy(dest, "");
    src_length = strlen(src);
    sub_length = strlen(sub);

    if (k < 0) {
        sub_length = abs(k);
        k = 0;
    }

    before_substring = substr(src, 0, k);
    strcat(dest, before_substring);

    cropped_substring = substr(sub, 0, sub_length);
    strcat(dest, cropped_substring);

    after_substring = substr(src, k, src_length - k);
    strcat(dest, after_substring);

    free(before_substring);
    free(cropped_substring);
    free(after_substring);
}

static void strins4(char *dest, const char *src, const char *sub, int k) {
    int src_length, sub_length;

    strcpy(dest, src);
    src_length = strlen(src);
    sub_length = strlen(sub);

    if (sub_length > 0) {
        if (k < 0) {
            sub_length = abs(k);
            k = 0;
        } else if (k > src_length) {
            k = src_length;
        }

        memmove(dest + k + sub_length, dest + k, src_length - k + 1);
        memcpy(dest + k, sub, sub_length);
    }
}


/**
 * Четыре функции, реализующие алгоритм поиска
 * подстроки в строке.
 * @param src исходная строка;
 * @param sub искомая подстрока;
 * @return позиция подстроки в строке.
 */

int strpos1(const char *src, const char *sub) {
    int result = 0;

    if (strlen(sub) == 0)
        return 0;

    while (*src != 0) {
        if (*src == *sub) {
            for (char *r = (char *) src, *t = (char *) sub; *t != 0;)
                if (*t++ != *r++) goto next_dest;
            return result;
        }
        next_dest:
        src++;
        result++;
    }

    return -1;
}

int strpos2(const char *src, const char *sub) {
    int i, j, result;

    int src_length = strlen(src);
    int sub_length = strlen(sub);

    if (sub_length == 0)
        return 0;

    for (i = 0; i <= src_length - sub_length; i++) {
        result = i;

        for (j = 0; j < sub_length; j++)
            if (src[result] == sub[j])
                if (j == sub_length - 1)
                    return result - sub_length + 1;
                else
                    result++;
            else
                break;

    }

    return -1;
}

int strpos3(const char *src, const char *sub) {
    int i, j, temp_i;

    int src_length = strlen(src);
    int sub_length = strlen(sub);

    if (sub_length == 0)
        return 0;

    if (sub_length > src_length)
        return -1;

    for (i = 0; i <= src_length; i++) {
        j = 0;
        if (src[i] == sub[j]) {
            temp_i = i;
            while (src[temp_i] == sub[j] && j < sub_length) {
                j++;
                temp_i++;
            }

            if (j == sub_length)
                return i;
        }
    }

    return -1;
}

int strpos4(const char *src, const char *sub) {
    int i;
    int temp_sub_pos = 0;

    int src_length = strlen(src);
    int sub_length = strlen(sub);

    for (i = 0; i < src_length; i++) {
        if (temp_sub_pos == sub_length)
            break;

        if (sub[temp_sub_pos] == src[i])
            temp_sub_pos++;
        else {
            if (temp_sub_pos > 0)
                i -= temp_sub_pos;

            temp_sub_pos = 0;
        }
    }

    if (temp_sub_pos < sub_length)
        return -1;
    else
        return i - temp_sub_pos;
}

void convertVarArgIntoVector(vector<const char *> &dest, const char *varargs, ...) {
    vector<char *> res;
    va_list args;
    va_start(args, varargs);

    while (*varargs != '\0') {
        auto i = va_arg(args, const char *);
        dest.push_back(i);
        printf("%s", i);
        ++varargs;
    }

    va_end(args);
}

char *strcat1(int k, ...) {
    va_list args;
    va_start(args, k);

    auto result = new char[1000];
    int result_pos = 0;

    for (int j = 0; j < k; j++) {
        auto i = va_arg(args, char *);
        if (i == nullptr)
            break;

        while (*i != '\0')
            result[result_pos++] = *i++;
    }

    result[result_pos] = '\0';

    va_end(args);

    return result;
}

char *strcat2(int k, ...) {
    va_list args;
    va_start(args, k);

    auto result = new char[1000];
    int result_pos = 0;

    while (k--) {
        char *i;
        i = va_arg(args, char *);

        if (i == nullptr)
            break;

        while (*i != '\0')
            result[result_pos++] = *i++;
    }

    result[result_pos] = '\0';

    va_end(args);

    return result;
}

char *strcat3(int k, ...) {
    va_list args;
    va_start(args, k);

    auto result = new char[1000];
    int result_pos = 0;

    while (true) {
        char *i;
        i = va_arg(args, char *);

        if (i == nullptr)
            break;

        while (*i != '\0')
            result[result_pos++] = *i++;
    }

    result[result_pos] = '\0';

    va_end(args);

    return result;
}


/**
 * Выводит тесты всех функций strlen.
 * @param s исходная строка.
 */
static void test_strlen(const char *value) {
    char *input_params;
    input_params = new char[200];
    strcpy(input_params, "");

    strcat(input_params, "s = \"");
    strcat(input_params, value);
    strcat(input_params, "\"");

    print_before_test(to_string(strlen(value)), input_params);
    free(input_params);

    printf("strlen1(\"%s\")=%lld\n", value, strlen1(value));
    printf("strlen2(\"%s\")=%lld\n", value, strlen2(value));
    printf("strlen3(\"%s\")=%lld\n", value, strlen3(value));
    printf("strlen4(\"%s\")=%lld\n", value, strlen4(value));

    enter_to_continue();
}

/**
 * Выводит тесты всех функций strcmp.
 * @param s1 первая строка;
 * @param s2 вторая строка.
 */
static void test_strcmp(const char *s1, const char *s2) {
    char *input_params;
    input_params = new char[200];
    strcpy(input_params, "");

    strcpy(input_params, "");
    strcat(input_params, "s1 = \"");
    strcat(input_params, s1);
    strcat(input_params, "\", s2 = \"");
    strcat(input_params, s2);
    strcat(input_params, "\"");

    print_before_test(to_string(strcmp(s1, s2)), input_params);
    free(input_params);

    printf("strcmp1(\"%s\", \"%s\")=%d\n", s1, s2, strcmp1(s1, s2));
    printf("strcmp2(\"%s\", \"%s\")=%d\n", s1, s2, strcmp2(s1, s2));
    printf("strcmp3(\"%s\", \"%s\")=%d\n", s1, s2, strcmp3(s1, s2));
    printf("strcmp4(\"%s\", \"%s\")=%d\n", s1, s2, strcmp4(s1, s2));

    enter_to_continue();
}

/**
 * Выводит тесты всех функций strcpy.
 * @param dest куда копировать;
 * @param src что копировать.
 */
static void test_strcpy(const char *dest, const char *src) {
    char *input_params;
    input_params = new char[200];
    strcpy(input_params, "");

    strcat(input_params, "dest = \"");
    strcat(input_params, dest);
    strcat(input_params, "\", src = \"");
    strcat(input_params, src);
    strcat(input_params, "\"");

    print_before_test(src, input_params);
    free(input_params);

    char *destination;
    destination = new char[max(strlen(dest), strlen(src)) + 1];
    strcpy((char *) destination, dest);
    strcpy1((char *) destination, src);
    printf("strcpy1(\"%s\", \"%s\")=%s\n", dest, src, destination);

    strcpy((char *) destination, dest);
    strcpy2((char *) destination, src);
    printf("strcpy2(\"%s\", \"%s\")=%s\n", dest, src, destination);

    strcpy((char *) destination, dest);
    strcpy3((char *) destination, src);
    printf("strcpy3(\"%s\", \"%s\")=%s\n", dest, src, destination);

    strcpy((char *) destination, dest);
    strcpy4((char *) destination, src);
    printf("strcpy4(\"%s\", \"%s\")=%s\n", dest, src, destination);

    enter_to_continue();
}

/**
 * Выводит тесты всех функций strins.
 * @param s1 первая строка;
 * @param s2 вторая строка.
 */
static void test_strins(const char *dest, const char *src, const char *sub, int k) {
    char *input_params;
    input_params = new char[250];
    strcpy(input_params, "");

    strcat(input_params, "dest = \"");
    strcat(input_params, dest);
    strcat(input_params, "\", src = \"");
    strcat(input_params, src);
    strcat(input_params, "\", sub = \"");
    strcat(input_params, sub);
    strcat(input_params, "\", k = ");
    strcat(input_params, to_string(k).c_str());

    int src_length = strlen(src);
    int sub_length = strlen(sub);

    string temp = src;
    if (k > src_length)
        temp.insert(src_length, sub);
    else if (k >= 0)
        temp.insert(k, sub);
    else
        temp.insert(0, sub, abs(k));

    print_before_test(temp, input_params);
    free(input_params);

    char *new_temp;
    new_temp = nullptr;
    new_temp = new char[src_length + sub_length + 40];
    strcpy(new_temp, dest);
    strins1(new_temp, src, sub, k);
    printf("strins1(\"%s\", \"%s\", \"%s\", %d) -> dest=\"%s\"\n",
           dest, src, sub, k, new_temp);

    new_temp = new char[src_length + sub_length + 40];
    strcpy(new_temp, dest);
    strins2(new_temp, src, sub, k);
    printf("strins2(\"%s\", \"%s\", \"%s\", %d) -> dest=\"%s\"\n",
           dest, src, sub, k, new_temp);

    new_temp = new char[src_length + sub_length + 40];
    strcpy(new_temp, dest);
    strins3(new_temp, src, sub, k);
    printf("strins3(\"%s\", \"%s\", \"%s\", %d) -> dest=\"%s\"\n",
           dest, src, sub, k, new_temp);

    new_temp = new char[src_length + sub_length + 40];
    strcpy(new_temp, dest);
    strins4(new_temp, src, sub, k);
    printf("strins4(\"%s\", \"%s\", \"%s\", %d) -> dest=\"%s\"\n",
           dest, src, sub, k, new_temp);

    enter_to_continue();
}

/**
 * Выводит тесты всех функций strpos.
 * @param s1 первая строка;
 * @param s2 вторая строка.
 */
static void test_strpos(const char *src, const char *sub) {
    char *input_params;
    input_params = new char[200];
    strcpy(input_params, "");

    strcat(input_params, "src = \"");
    strcat(input_params, src);
    strcat(input_params, "\", sub = \"");
    strcat(input_params, sub);
    strcat(input_params, "\"");

    string src_string(src);
    auto pos = src_string.find(sub);
    string expected_result;
    if (pos > strlen(src))
        expected_result = "-1";
    else
        expected_result = to_string(pos);

    print_before_test(expected_result, input_params);
    free(input_params);

    printf("strpos1(\"%s\", \"%s\")=%d\n", src, sub, strpos1(src, sub));
    printf("strpos2(\"%s\", \"%s\")=%d\n", src, sub, strpos2(src, sub));
    printf("strpos3(\"%s\", \"%s\")=%d\n", src, sub, strpos3(src, sub));
    printf("strpos4(\"%s\", \"%s\")=%d\n", src, sub, strpos4(src, sub));

    enter_to_continue();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        n = 0;
        set_color(11);
        printf("Выберите функцию для тестирования:\n");
        set_color(7);
        printf("1. Длина строки (strlen).\n");
        printf("2. Сравнение строк (strcmp).\n");
        printf("3. Вставка подстроки в строку (strins).\n");
        printf("4. Позиция подстроки в строке (strpos).\n");
        printf("5. Копирование строки в другую строку (strcpy).\n");
        printf("6. Объединение нескольких строк в одну строку. (strcat).\n");
        printf("0. Выйти из программы.\n");

        input(0, 6, n);


        set_color(11);
        printf("\nВыбрана функция: ");
        set_color(7);

        if (n == 0)
            break;
        else if (n == 1) {


            printf("Длина строки (strlen).\n\n");

            test_strlen("");
            test_strlen("Нет ничего важнее семьи...");


        } else if (n == 2) {


            printf("Сравнение строк (strcmp).\n\n");

            test_strcmp("Never", ""); // Сравнение с пустой строкой
            test_strcmp("Gonna", "Give you"); // Первая строка больше, но короче
            test_strcmp("Up! Never", "Gonna"); // Первая строка больше и длиннее
            test_strcmp("Let u", "Down!"); // Первая строка больше и имеет такую же длину, как и вторая
            test_strcmp("Never gonna", "Run"); // Вторая строка больше, но короче
            test_strcmp("Around", "And desert you!"); // Вторая строка больше и длиннее
            test_strcmp("Never gonna let you cry!",
                        "Never gonna say goodbye!"); // Вторая строка больше и имеет такую же длину, как и первая


        } else if (n == 3) {


            printf("Вставка подстроки в строку (strins).\n\n");

            char *src, *sub;
            int src_length, sub_length;

            set_color(10);
            printf("Выберите пакет тестов (исходная строка):\n");
            set_color(7);
            printf("1. Src пуста.\n");
            printf("2. Src не пуста. Значение с клавиатуры.\n");
            printf("3. Src не пуста. Стандартное значение.\n");

            input(1, 3, n);

            if (n == 1) {
                src = new char[1];
                strcpy(src, "");
            } else if (n == 2) {
                src = new char[51];

                set_color(11);
                printf("Введите исходную строку (src) (до 50 символов):\n");

                set_color(6);
                printf("> ");

                set_color(7);
                scanf("%s", src);
            } else {
                src = new char[14];
                strcpy(src, "Roses are red");
            }

            set_color(10);
            printf("Выберите пакет тестов (вставляемая строка):\n");
            set_color(7);
            printf("1. Sub пуста.\n");
            printf("2. Sub не пуста. Значение с клавиатуры.\n");
            printf("3. Sub не пуста. Стандартное значение.\n");

            input(1, 3, n);

            if (n == 1) {
                sub = new char[1];
                strcpy(sub, "");
            } else if (n == 2) {
                sub = new char[51];

                set_color(11);
                printf("Введите вставляемую строку (sub) (до 50 символов):\n");

                set_color(6);
                printf("> ");

                set_color(7);
                scanf("%s", sub);
            } else {
                sub = new char[17];
                strcpy(sub, "Violets are blue");
            }

            printf("\n");

            src_length = strlen(src);
            sub_length = strlen(sub);

            if (src_length > 0)
                test_strins("", src, sub, sub_length / 2); // k > 0, k < strlen(src)
            else {
                set_color(12); //  Красный
                printf("k > 0, k < strlen(src) - невозможно, ибо strlen(src) = 0\n");
                enter_to_continue();
            }
            test_strins("", src, sub, 0 - ceil((double) sub_length / 2)); // k < 0
            test_strins("", src, sub, src_length + 2); // k > strlen(src)
            test_strins("", src, sub, 0); // k = 0
            test_strins("", src, sub, src_length); // k = strlen(src)


        } else if (n == 4) {


            printf("Позиция подстроки в строке (strpos).\n\n");


            char *src, *sub;
            int src_length, sub_length;

            set_color(10);
            printf("Выберите пакет тестов (исходная строка):\n");
            set_color(7);
            printf("1. Src пуста.\n");
            printf("2. Src не пуста. Стандартное значение.\n");

            input(1, 2, n);

            if (n == 1) {
                src = new char[2];
                strcpy(src, "");
            } else {
                src = new char[90];
                strcpy(src, "бери ружьё, седлай коня. скачи судьбе навстречу!");
            }

            src_length = strlen(src);

            test_strpos(src, ""); // Sub пуста
            test_strpos(src, "ну, а выпьешь - вспомни про меня."); // Sub не пуста, вхождений в src нет
            test_strpos(src, "бери"); // Sub не пуста, имеется единственное вхождение с символа 0

            if (src_length > 5)
                test_strpos(src, "коня."); // Sub не пуста, имеется единственное вхождение с символа 0
            else {
                set_color(12); // Красный
                printf("0 < k < strlen(src)-strlen(sub) - невозможно, ибо strlen(src) <= strlen(sub)\n");
                enter_to_continue();
            }

            if (src_length > 10)
                test_strpos(src,
                            "навстречу!"); // Sub не пуста, имеется единственное вхожение с символа strlen(src) - strlen(sub)
            else {
                set_color(12);
                printf("k = strlen(src)-strlen(sub) - невозможно, ибо strlen(src) < strlen(sub)\n");
                enter_to_continue();
            }

            test_strpos(src, "бе"); // Sub не пуста, имеется несколько вхождений в Src

        } else if (n == 5) {


            printf("Копирование строки в другую строку (strcpy).\n\n");

            test_strcpy("", "Было пусто, стало густо.");
            test_strcpy("Крым, Украина.", "Крым, Россия.");


        } else if (n == 6) {


            printf("6. Объединение нескольких строк в одну строку. (strdel).\n");

            printf("%s\n", strcat1(5, (char *) "niggers", "are", "lmao", "lol", "kek\0 \0"));
            printf("%s\n", strcat2(5, (char *) "niggers", "are", "lmao", "lol", "kek\0 \0"));
            printf("%s\n", strcat3(5, (char *) "niggers", "are", "lmao", "lol", "kek\0 \0"));
//            printf("%s\n", strcat1(4, "213", "213", "213", "213"));

        } else
            printf("Как так вышло, что тут прошло это число?..");
    }

    return 0;
}

#pragma clang diagnostic pop