#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 50

struct videocards{
    char brand[10];
    int perform;
    int price;
    char gpu[10];
    int memory;
};
typedef struct videocards cards;

void print_card (cards* card, int* size);                                                //вывод звписей
void s_print_card (cards* s_card, int* s_i);                                             //вывод сортированных записей
cards* input_card(cards* card, int* size, int me, int pe, int pr, char* br, char* gp);   //запись в фaйл
cards* sort_memory(cards* card, int size, int f);                                        //сортировка по оъему памяти
int sort_memory_h(const void* x, const void* y);                                         //сортировка по оъему памяти возрастание
int sort_memory_l(const void* x, const void* y);                                         //сортировка по оъему памяти убывание
cards* edit_card(cards* card, int numb, char* x1, int x3, int x4, char* x2, int x5);     //редактирование записей
cards* delet_card(cards* card, int size, int n);                                         //удаление записи
cards* search_brand(cards* card, cards* s_card, int* size, char* s_brand);               //поиск по бренду
cards* search_memory(cards* card, cards* s_card, int* size, int s_memory);               //поиск по объему памяти
cards* search_1(cards* card, cards* s_card, int* size, char* s_brand, int s_price);      //поиск записи по бренду и цене
cards* search_2(cards* card, cards* s_card, int* size, int s_perform, int s_memory);     //поиск по производительности объему памяти
cards* search_3(cards* card, cards* s_card, int* size, int s_price, char* s_gpu);        //поиск по цене и графическому процессору
cards* search_4(cards* card, cards* s_card, int* size, char* s_brand, char* s_gpu);      //поиск по графическому процессору и бренду
cards* search_5(cards* card, cards* s_card, int* size, int s_price, int s_memory);       //поиск по объему памяти и цене
FILE* write_cards(FILE* file, cards* card, int size);                                    //запись в файл с измененниями

int main(void)
{
    FILE *file = fopen("/Users/kirillpustovojt/Desktop/Labs/Kursach/Kursach/kursovidio.txt", "r+");
    if (file == NULL) puts("Ошибка открытия файла.\n");
    cards* card = calloc(N, sizeof(cards));
    cards* s_card = calloc(N, sizeof(cards));
    int size = 0;
    char cm = ' ', cr = ' ';
    printf("%45c<<Программа для работы с файловой базой данных видеокарт сети магазинов DNS>>\n%45c-----------------------------------------------------------------------------\n%45c| Группа: бИСТ-233%45c             |\n%45c-----------------------------------------------------------------------------\n%45c| Выполнил: Пустовойт К. А.%45c    |\n%45c-----------------------------------------------------------------------------\n%45c| Руководитель: Курипта О. В.%45c  |\n%45c-----------------------------------------------------------------------------\n%45c| Программа предназначена представляет собой файловую базу данных, осущес-  |\n%45c| твляющую сортировку, поиск, редактирование и вывод данных из файла        |\n%45c-----------------------------------------------------------------------------\n\n",cm,cm,cm,cm,cm,cm,cm,cm,cm,cm,cm,cm,cm,cm);
    while (cm != '0'){
        printf("Выберите действие:\n'1' -> Загрузить данные из файла\n'2' -> Добавить новую запись\n'3' -> Поиск записи по параметру\n'4' -> Сортировка по объему памяти\n'5' -> Изменить существующую запись\n'6' -> Удалить запись\n'7' -> Сохранить данные в файл\n'0' -> Выйти\n>\n");
        scanf("%c", &cm);
        
        switch (cm){
                
            case '1':
                while (fscanf(file, "%s %d %d %s %d", card[size].brand, &card[size].perform, &card[size].price, card[size].gpu, &card[size].memory) == 5) size++;
                printf("Загрузка данных прошла успешно!\nВ файле %d записи(ей)", size);
                print_card (card, &size);
                getchar();
                break;
                
            case '2':{
                int pe,pr,me;
                char br[10], gp[10];
                puts("Введите следующие данные через пробел для создания новой записи: Бренд, Производительность, Цена, Тип графического процессора, Объем памяти\n");
                scanf("%s %d %d %s %d", br, &pe, &pr, gp, &me);
                input_card(card, &size, me, pe, pr, br, gp);
                puts("Новая запись успешно добавлена!\n");
                getchar();
                break;
            }
                
            case '3':{
                    int I;
                    puts("Как хотите произвести поиск?\n'1' - По одному переметру\n'2' - По двум параметрам\n");
                    scanf("%d", &I);
                    if (I == 1){
                        while (cr != '0'){
                            char s_brand[10];
                            int s_memory;
                            puts("\nВыберете параметр поиска:\n'1' - Brand\n'2' - Memory\n'0' - Перейти в главное меню\n>");
                            scanf("%c", &cr);
                            switch (cr){
                                    
                                case '1':
                                    puts("Введите название бренда:\n");
                                    scanf("%s", s_brand);
                                    search_brand(card, s_card, &size, s_brand);
                                    break;
                                    
                                case '2':
                                    puts("Введите объем памяти:\n");
                                    scanf("%d", &s_memory);
                                    search_memory(card, s_card, &size,s_memory);
                                    break;
                                    
                                default:
                                    break;
                            }
                        }
                    }
                    if (I == 2){
                        while (cr != '0'){
                            char s_brand[10],s_gpu[10];
                            int s_perform, s_price,s_memory;
                            puts("\nВыберете параметр поиска:\n'1' - Brand and Price\n'2' - Perfprm and Memory\n'3' - Price and GPU\n'4' - Brand and GPU\n'5' - Price and Memory\n'0' - Перейти в главное меню\n>");
                            scanf("%c", &cr);
                            switch (cr){
                                    
                                case '1':
                                    puts("Введите название бренда:");
                                    scanf("%s", s_brand);
                                    puts("Введите цену:");
                                    scanf("%d", &s_price);
                                    search_1(card, s_card, &size, s_brand, s_price);
                                    break;
                                    
                                case '2':
                                    puts("Введите производительность:");
                                    scanf("%d", &s_perform);
                                    puts("Введите объем памяти:");
                                    scanf("%d", &s_memory);
                                    search_2(card, s_card, &size, s_perform, s_memory);
                                    break;
                                    
                                case '3':
                                    puts("Введите цену:");
                                    scanf("%d", &s_price);
                                    puts("Введите графический процессор (discrete/built):");
                                    scanf("%s", s_gpu);
                                    search_3(card, s_card, &size, s_price, s_gpu);
                                    break;
                                    
                                case '4':
                                    puts("Введите название бренда:");
                                    scanf("%s", s_brand);
                                    puts("Введите графический процессор (discrete/built):\n");
                                    scanf("%s", s_gpu);
                                    search_4(card, s_card, &size, s_brand, s_gpu);
                                    break;
                                    
                                case '5':
                                    puts("Введите цену:");
                                    scanf("%d", &s_price);
                                    puts("Введите объем памяти:\n");
                                    scanf("%d", &s_memory);
                                    search_5(card, s_card, &size, s_price, s_memory);
                                    break;
                                    
                                default:
                                    break;
                            }
                        }
                    }
                    else puts("Bruh.\n");
                }
                getchar();
                break;
                
                
            case '4':{
                int f = 3;
                puts("Как отфильтровать?\n'1' - По возрастанию\n'2' - По убыванию\n'0' - Выход в главное меню\n");
                scanf("%d", &f);
                sort_memory(card,size,f);
                getchar();
                break;
            }
                
            case '5':{
                int numb;
                print_card (card, &size);
                printf("Введите номер записи, которую хотите отредактировать:");
                scanf("%d", &numb);
                int x3 ,x4,x5;
                char x1[10], x2[10];
                puts("Производитель:");
                scanf("%s", x1);
                puts("Производительность:");
                scanf("%d", &x3);
                puts("Цена:");
                scanf("%d", &x4);
                puts("Тип процессора:");
                scanf("%s", x2);
                puts("Объем памяти: ");
                scanf("%d", &x5);
                edit_card(card,numb, x1, x3, x4, x2, x5);
                getchar();
                break;
            }
                
            case '6':{
                print_card (card, &size);
                int numb;
                printf("Введите номер записи, которую хотите удалить:");
                scanf("%d", &numb);
                int n = numb;
                delet_card(card,size,n);
                getchar();
                break;
            }
                
            case '7':
                write_cards(file,card,size);
                puts("Данные успешно сохранены!");
                getchar();
                break;
                
            default:
                break;
                
        }
        fclose(file);
    }
}

void print_card (cards* card, int* size){
    char c = ' ';
    printf("\n%45c---------------------------------------------------------------------------------------\n%45c|%2c<Numb>%2c|%3c<Brand>%3c|%3c<Perform>%3c|%3c<Price>%3c|%5c<GPU>%5c|%3c<Memory>%3c|\n",c,c,c,c,c,c,c,c,c,c,c,c,c,c);
    for (int i = 0; i < *size; ++i){
        printf("%45c---------------------------------------------------------------------------------------\n%45c|%2c%6d%2c|%3c%7s%3c|%3c%9d%3c|%3c%7d%3c|%3c%9s%3c|%3c%8d%3c|\n", c, c, c, i+1,c,c,card[i].brand,c,c, card[i].perform,c,c, card[i].price,c,c, card[i].gpu,c,c, card[i].memory,c);
    }
    printf("%45c---------------------------------------------------------------------------------------\n",c);
}

void s_print_card (cards* s_card, int* s_size){
    char c = ' ';
    printf("\n%45c---------------------------------------------------------------------------------------\n%45c|%2c<Numb>%2c|%3c<Brand>%3c|%3c<Perform>%3c|%3c<Price>%3c|%5c<GPU>%5c|%3c<Memory>%3c|\n",c,c,c,c,c,c,c,c,c,c,c,c,c,c);
    for (int i = 0; i < *s_size; ++i){
        printf("%45c---------------------------------------------------------------------------------------\n%45c|%2c%6d%2c|%3c%7s%3c|%3c%9d%3c|%3c%7d%3c|%3c%9s%3c|%3c%8d%3c|\n", c, c, c, i+1,c,c,s_card[i].brand,c,c, s_card[i].perform,c,c, s_card[i].price,c,c, s_card[i].gpu,c,c, s_card[i].memory,c);
    }
    printf("%45c---------------------------------------------------------------------------------------\n",c);
}

cards* input_card(cards* card, int* size, int me, int pe, int pr, char* br, char* gp){
    card[*size].perform = pe;
    card[*size].price = pr;
    card[*size].memory = me;
    for (int f = 0; f < 10; ++f){
        (card[*size].brand)[f] = br[f];
        (card[*size].gpu)[f] = gp[f];
    }
    (*size)++;
    print_card (card, size);
    return card;
}

cards* search_brand(cards* card, cards* s_card, int* size, char* s_brand){
    int point = 0, s_i = 0;
    for (int i = 0; i < *size; ++i){
        if (strcmp(card[i].brand, s_brand) == 0 ){
            s_card[s_i].perform = card[i].perform;
            s_card[s_i].price = card[i].price;
            s_card[s_i].memory = card[i].memory;
            for (int f = 0; f < 10; ++f){
                ( s_card[s_i].brand)[f] = (card[i].brand)[f];
                (s_card[s_i].gpu)[f] = (card[i].gpu)[f];
            }
            s_i++;
            point = 1;
        }
    }
    if (!point){
        printf("Bruh.\n");
    }
    s_print_card (s_card, &s_i);
    return s_card;
}

cards* search_1(cards* card, cards* s_card, int* size, char* s_brand, int s_price){
    int point = 0, s_i = 0;
    for (int i = 0; i < *size; ++i){
        if (strcmp(card[i].brand, s_brand) == 0 && card[i].price == s_price){
            s_card[s_i].perform = card[i].perform;
            s_card[s_i].price = card[i].price;
            s_card[s_i].memory = card[i].memory;
            for (int f = 0; f < 10; ++f){
               ( s_card[s_i].brand)[f] = (card[i].brand)[f];
                (s_card[s_i].gpu)[f] = (card[i].gpu)[f];
            }
            s_i++;
            point = 1;
        }
    }
    if (!point){
        printf("Bruh.\n");
    }
    s_print_card (s_card, &s_i);
    return s_card;
}

cards* search_2(cards* card, cards* s_card, int* size, int s_perform, int s_memory){
    int point = 0, s_i = 0;
    for (int i = 0; i < *size; ++i){
        if (card[i].perform == s_perform && card[i].memory == s_memory){
            s_card[s_i].perform = card[i].perform;
            s_card[s_i].price = card[i].price;
            s_card[s_i].memory = card[i].memory;
            for (int f = 0; f < 10; ++f){
               ( s_card[s_i].brand)[f] = (card[i].brand)[f];
                (s_card[s_i].gpu)[f] = (card[i].gpu)[f];
            }
            s_i++;
            point = 1;
        }
    }
    if (!point){
        printf("Bruh.\n");
    }
    s_print_card (s_card, &s_i);
    return s_card;
}

cards* search_3(cards* card, cards* s_card, int* size, int s_price, char* s_gpu){
    int point = 0, s_i = 0;
    for (int i = 0; i < *size; ++i){
        if (card[i].price == s_price && strcmp(card[i].gpu, s_gpu) == 0){
            s_card[s_i].perform = card[i].perform;
            s_card[s_i].price = card[i].price;
            s_card[s_i].memory = card[i].memory;
            for (int f = 0; f < 10; ++f){
               ( s_card[s_i].brand)[f] = (card[i].brand)[f];
                (s_card[s_i].gpu)[f] = (card[i].gpu)[f];
            }
            s_i++;
            point = 1;
        }
    }
    if (!point){
        printf("Bruh.\n");
    }
    s_print_card (s_card, &s_i);
    return s_card;
}

cards* search_4(cards* card, cards* s_card, int* size, char* s_brand, char* s_gpu){
    int point = 0, s_i = 0;
    for (int i = 0; i < *size; ++i){
        if (strcmp(card[i].gpu, s_gpu) == 0 && strcmp(card[i].brand, s_brand) == 0){
            s_card[s_i].perform = card[i].perform;
            s_card[s_i].price = card[i].price;
            s_card[s_i].memory = card[i].memory;
            for (int f = 0; f < 10; ++f){
               ( s_card[s_i].brand)[f] = (card[i].brand)[f];
                (s_card[s_i].gpu)[f] = (card[i].gpu)[f];
            }
            s_i++;
            point = 1;
        }
    }
    if (!point){
        printf("Bruh.\n");
    }
    s_print_card (s_card, &s_i);
    return s_card;
}

cards* search_5(cards* card, cards* s_card, int* size, int s_price, int s_memory){
    int point = 0, s_i = 0;
    for (int i = 0; i < *size; ++i){
        if (card[i].memory == s_memory && card[i].price == s_price){
            s_card[s_i].perform = card[i].perform;
            s_card[s_i].price = card[i].price;
            s_card[s_i].memory = card[i].memory;
            for (int f = 0; f < 10; ++f){
               ( s_card[s_i].brand)[f] = (card[i].brand)[f];
                (s_card[s_i].gpu)[f] = (card[i].gpu)[f];
            }
            s_i++;
            point = 1;
        }
    }
    if (!point){
        printf("Bruh.\n");
    }
    s_print_card (s_card, &s_i);
    return s_card;
}

cards* search_memory(cards* card, cards* s_card, int* size, int s_memory){
    int point = 0, s_i = 0;
    for (int i = 0; i < *size; ++i){
        if (card[i].memory == s_memory){
            s_card[s_i].perform = card[i].perform;
            s_card[s_i].price = card[i].price;
            s_card[s_i].memory = card[i].memory;
            for (int f = 0; f < 10; ++f){
               ( s_card[s_i].brand)[f] = (card[i].brand)[f];
                (s_card[s_i].gpu)[f] = (card[i].gpu)[f];
            }
            s_i++;
            point = 1;
        }
    }
    if (!point){
        printf("Bruh.\n");
    }
    s_print_card (s_card, &s_i);
    return s_card;
}

cards* sort_memory(cards* card, int size, int f){
    if (f==1 || f==2 || f==0){
        while (f != 0){
            switch(f){
                    
                case 1:
                    qsort(card, size, sizeof(cards), sort_memory_h);
                    print_card (card, &size);
                    puts("Записи успешно упорядочены!\n");
                    return card;
                    break;
                    
                case 2:
                    qsort(card, size, sizeof(cards), sort_memory_l);
                    print_card (card, &size);
                    puts("Записи успешно упорядочены!\n");
                    return card;
                    break;
                    
                case 0:
                    puts("Bruh.\n");
                    break;
                    return 0;
                    
                default:
                    break;
            }
        }
    }
    else puts("Bruh.\n");
    return 0;
}

int sort_memory_h(const void* x, const void* y){
    int sorted = ((cards*)x)->memory - ((cards*)y)->memory;
    return sorted;
}

int sort_memory_l(const void* x, const void* y){
    int sorted = ((cards*)y)->memory - ((cards*)x)->memory;
    return sorted;
}

cards* edit_card(cards* card, int numb, char* x1, int x3, int x4, char* x2, int x5){
    int num = numb - 1;
    (card + num)->perform = x3;
    (card + num)->price = x4;
    (card + num)->memory = x5;
    for (int f = 0; f < 10; ++f){
        ((card + num)->brand)[f] = x1[f];
        ((card + num)->gpu)[f] = x2[f];
    }
    return card;
}

cards* delet_card(cards* card, int size, int n){
    for (int i = n - 1; i <= size; ++i){
        if (i < size){
            card[i].perform = card[i+1].perform;
            card[i].price = card[i+1].price;
            card[i].memory = card[i+1].memory;
            for( int f = 0; f < 10;++f){
                (card[i].brand)[f] = (card[1+i].brand)[f];
                (card[i].gpu)[f] = (card[1+i].gpu)[f];
            }
        }
    }
    puts("Запись успешно удалена!");
    return card;
}

FILE* write_cards(FILE* file, cards* card, int size){
    fopen("/Users/kirillpustovojt/Desktop/Labs/Kursach/Kursach/kursovidio.txt", "w+");
    for (int i = 0; i < size; ++i){
        fprintf(file,"%s %d %d %s %d\n",card[i].brand, card[i].perform, card[i].price, card[i].gpu, card[i].memory);
    }
    return (file = fopen("/Users/kirillpustovojt/Desktop/Labs/Kursach/Kursach/kursovidio.txt", "r+"));
}
