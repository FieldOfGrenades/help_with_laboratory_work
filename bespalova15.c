// 5. Пусть задано N отрезков 
// с помощью координат их концов. Определить длины  
// наибольшего и наименьшего из них, также вывести их координаты.

#include <stdio.h>
#include <locale.h>
#include <climits>//для возможности использования константами переменных(строка 74, 96)

// структура текстового файла
// 1) количество отрезков
// 2) координаты х y
// .................
// n) координаты х y

// структура, хранящая координаты двух отрезков
struct segments
{
	// координаты отрезка
	double x, y;
};

// получает ссылку на массив структур и номер элемента в массиве
// выводит элемент под номером number_of_segment
// пробел перед %lf чтобы при выводе не слиплялось с другим выводом
void print_segment(struct segments* list, int number_of_segment)
{
	printf_s(" (%lf, %lf)\n", list[number_of_segment].x, list[number_of_segment].y);
}

//полчает указатель на структуру, желаемый размер считывания, название файла
//вводит структуру из файла
int input_struct_from_file(struct segments* list, char* filename)
{
	FILE* fp; int n = 0;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("Не удалось открыть файл\n");
	}
	else
	{
		fscanf_s(fp, "%d\n", &n);
		// ввод массива из текстого файла
		for (int i = 0; i < n; i++)
		{
			fscanf_s(fp, "%lf%lf", &list[i].x, &list[i].y);
		}
		// закрытие файла
		fclose(fp);
	}
	return n;
}

// получает массив структур и его размер
// возвращает номер самого короткого отрезка
int find_shortest_segment(struct segments* list, int n)
{
	double min_size_of_segmets = INT_MAX;
	int number_of_shortest_segment = 1;
	// осуществляем проход по структуре
	for (int i = 0; i < n; i++)
	{
		// если отрезок меньше огромного числа (выбранного для нахождения минимума)
		// то
		if ((list[i].y - list[i].x) < min_size_of_segmets)
		{
			// минимальную длинну отрезка заменяем текущей
			min_size_of_segmets = list[i].y - list[i].x;
			// сохраняем номер элемента
			number_of_shortest_segment = i;
		}
	}
	return number_of_shortest_segment;
}

// получает массив структур и его размер
// возвращает номер самого короткого отрезка
int find_longest_segment(struct segments* list, int n)
{
	double max_size_of_segmets = INT_MIN;
	int number_of_longest_segment = 0;
	// осуществляем проход по структуре
	for (int i = 0; i < n; i++)
	{
		// если отрезок больше маленького числа (выбранного для нахождения максимума)
		// то
		if ((list[i].y - list[i].x) > max_size_of_segmets)
		{
			// минимальную длинну отрезка заменяем текущей
			max_size_of_segmets = list[i].y - list[i].x;
			// сохраняем номер элемента
			number_of_longest_segment = i;
		}
	}
	return number_of_longest_segment;
}

//получает массив структур и его размер
//осуществляет ввод с клавиатуры пользователем
void input_struct_from_keyboard(struct segments* list, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf_s("Введите координату х: ");
		scanf_s("%lf", &list[i].x);
		printf_s("Введите координату y: ");
		scanf_s("%lf", &list[i].y);
	}
	printf_s("\n");//переход на новую строку
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	int choice;
	printf_s("1) Ввод с клавиатуры\n2) Из текстового файла\n");
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
	{
		int n;
		printf_s("Введите количество отрезков: ");
		scanf_s("%d", &n);
		if (n <= 20 && n >= 1)
		{
			struct segments list[20];
			input_struct_from_keyboard(list, n);
			int number_of_longest_segment = find_longest_segment(list, n);
			int number_of_shortest_segment = find_shortest_segment(list, n);
			printf_s("Координаты кротчайшего отрезка: ");
			print_segment(list, number_of_shortest_segment);
			printf_s("Координаты длиннейшего отрезка: ");
			print_segment(list, number_of_longest_segment);
		}
	}
	case 2:
	{
		char filename[30];
		struct segments list[20];
		printf_s("Введите название файла: ");
		scanf_s("%s", &*filename, sizeof(filename));
		int n = input_struct_from_file(list, filename);
		int number_of_longest_segment = find_longest_segment(list, n);
		int number_of_shortest_segment = find_shortest_segment(list, n);
		printf_s("Координаты кротчайшего отрезка: ");
		print_segment(list, number_of_shortest_segment);
		printf_s("Координаты длиннейшего отрезка: ");
		print_segment(list, number_of_longest_segment);
	}
	}
}
