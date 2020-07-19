#include <stdio.h>
int main(void)
{

    int i = 0;
    int idx;
    int studentId;
    struct score_data
    {
        int id;
        int math;
        int phys;
        int eng;
    };
    struct score_data data[50];

    FILE *fd, *wfd;
    fd = fopen("data.txt", "r");
    wfd = fopen("output.txt", "w");
    while (fscanf(fd, "%d: %d, %d, %d", &studentId, &data[studentId].math, &data[studentId].phys, &data[studentId].eng) != EOF)
    {
        data[studentId].id = studentId;
        printf("%d",idx);
        idx++;
    }

    // 小さいインデックス順（番号順）に対応する点数をプリントするが，
    // idが0ならその点数データは存在しない
    for (i = 1; i < 50; i++)
    {
        if (data[i].id != 0)
        {
            fprintf(wfd, "%d::%d: %d, %d, %d\n", i,data[i].id, data[i].math, data[i].phys, data[i].eng);
            printf("%d:%d,%d,%d\n", data[i].id, data[i].math, data[i].phys, data[i].eng);
        }
    }
    fclose(fd);
    fclose(wfd);

    return 0;
}
