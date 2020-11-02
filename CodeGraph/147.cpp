#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int id;
	char name[50];
	float chinese;
	float math;
	float english;
	float sum;
}student;

int ReadStuInfoFromFile(char *name, student **stu) {
    int n;
    FILE* fp;
    if (name == NULL) return 0;
    fp = fopen(name, "rb");
    if (fp == NULL) return 0;
    fread(&n, sizeof(int), 1, fp);
    *stu = (student*)malloc(sizeof(student) * n);
    for (int i = 0; i < n; i++) {
        fread(&((*stu)[i]), sizeof(struct student),1,fp);
        (*stu)[i].sum = (*stu)[i].math + (*stu)[i].english + (*stu)[i].chinese;
    }
    fclose(fp);
    return n;
}

int NoPass(student stu[], int n, student **noPassStudent, int *m) {
    if (n==0 || stu == NULL) {
		return -1;
	}
	*noPassStudent = (student*)malloc(sizeof(student) * n);
    float sum = 0.0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        sum += stu[i].sum;
    }
    sum = sum / n;
	for (int i = 0; i < n; i++) {
		if (stu[count].sum < sum) {
            noPassStudent[count] = &stu[i];
            count++;
		}
	}
    *m = count;
	return 0;
}

int Pass(student stu[], int n, student **PassStudent, int *m) {
    if (n==0 || stu == NULL) {
		return -1;
	}
	*PassStudent = (student*)malloc(sizeof(student) * n);
    float sum = 0.0;
    int count =0;
    for (int i = 0; i < n; i++) {
        sum += stu[i].sum;
    }
    sum = sum / n;
	for (int i = 0; i < n; i++) {
		if (stu[count].sum >= sum) {
            PassStudent[count] = &stu[i];
            count++;
		}
	}
    *m = count;
	return 0;
}

int SortStudents(student stu[], int n) {
    if (n==0 || stu == NULL) {
		return -1;
	}
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (stu[j].sum > stu[i].sum) {
                student tmp = stu[j];
                stu[j] = stu[i];
                stu[i] = tmp;
            }
        }
    }
    return 0;
}

int SearchStudent(student stu[], int n, int id,int *rank, student *rstu) {
    rstu = NULL;
	if (stu == NULL) return -1;
    SortStudents(stu, n);
	for (int i = 0; i < n; i++) {
		if (stu[i].id == id) {
			*rank = i + 1;
            *rstu = stu[i];
			return 0;
		}
	}
	if (rstu == NULL) return -1;
    return 0;
}
