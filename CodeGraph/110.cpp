#include <stdio.h>

struct Person {
    char Name[20];
    int sex;
    int brithday;
    double height;
    int c_grade, m_grade;
};

Person persons[10];
int num;

int c_max = -1, c_min = 200, m_min = 200, m_max = -1;
int c_sum = 0, m_sum = 0;

int main() {
    scanf("%d", &num);

    for (int i = 1; i <= num; i++) {
        scanf("%s %d %d %lf %d %d", persons[i].Name, &persons[i].sex,
            &persons[i].brithday, &persons[i].height, &persons[i].c_grade, &persons[i].m_grade);

            c_sum += persons[i].c_grade;
            m_sum += persons[i].m_grade;

            if (persons[i].m_grade < m_min) m_min = persons[i].m_grade;
            if (persons[i].m_grade > m_max) m_max = persons[i].m_grade;
            if (persons[i].c_grade < c_min) c_min = persons[i].c_grade;
            if (persons[i].c_grade > c_max) c_max = persons[i].c_grade;
    }

    c_sum /= num;
    m_sum /= num;

    printf("C_average:%d\n", c_sum);
    printf("C_max:%d\n", c_max);

    for (int i = 1; i <= num; i++) {
        if (persons[i].c_grade == c_max)
            printf ("%s %d %d %.2lf %d %d\n", persons[i].Name, persons[i].sex,
                persons[i].brithday, persons[i].height, persons[i].c_grade, persons[i].m_grade);
    }
    printf("C_min:%d\n", c_min);

    printf("Calculus_average:%d\n", m_sum);
    printf("Calculus_max:%d\n", m_max);

    for (int i = 1; i <= num; i++) {
        if (persons[i].m_grade == m_max)
            printf ("%s %d %d %.2lf %d %d\n", persons[i].Name, persons[i].sex,
                persons[i].brithday, persons[i].height, persons[i].c_grade, persons[i].m_grade);
    }
    printf("Calculus_min:%d\n", m_min);

    return 0;
}
