#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <dirent.h> 
#include <locale.h> 

#include <errno.h>
 
void process_directory(char *dir_path, FILE *csv_file, int *pdf_count, int *doc_count, int *txt_count, int *docx_count, int *png_count, int *jpeg_count, int *xls_count, int *xlsx_count, int *htm_count, int *html_count, int *jpg_count) { 
    DIR *dir; 
    struct dirent *ent; 
    if ((dir = opendir(dir_path)) != NULL) { 
        while ((ent = readdir(dir)) != NULL) { 
            char *file_name = ent->d_name; 
            if (strcmp(file_name, ".") == 0 || strcmp(file_name, "..") == 0) { 
                continue; 
            } 
 
            char file_path[1024]; 
            sprintf(file_path, "%s/%s", dir_path, file_name); 
 
            if (ent->d_type == DT_DIR) { 
                process_directory(file_path, csv_file, pdf_count, doc_count, txt_count, docx_count, png_count, jpeg_count, xls_count, xlsx_count, htm_count, html_count, jpg_count); 
            } else { 
                if (strstr(file_name,".pdf") != NULL) { 
                    (*pdf_count)++; 
                    fprintf(csv_file,"%s,%s\n",file_name,file_path); 
                } else if (strstr(file_name,".doc") != NULL) { 
                    (*doc_count)++; 
                    fprintf(csv_file,"%s,%s\n",file_name,file_path); 
                } else if (strstr(file_name,".txt") != NULL) { 
                    (*txt_count)++; 
                    fprintf(csv_file,"%s,%s\n",file_name,file_path); 
                } else if (strstr(file_name,".docx") != NULL) { 
                    (*docx_count)++; 
                    fprintf(csv_file,"%s,%s\n",file_name,file_path); 
                } else if (strstr(file_name,".png") != NULL) { 
                    (*png_count)++; 
                    fprintf(csv_file,"%s,%s\n",file_name,file_path); 
                } else if (strstr(file_name,".jpeg") != NULL) { 
                    (*jpeg_count)++;  
                    fprintf(csv_file,"%s,%s\n",file_name,file_path);  
                } else if (strstr(file_name,".xls") != NULL) {  
                    (*xls_count)++;  
                    fprintf(csv_file,"%s,%s\n",file_name,file_path);  
                } else if (strstr(file_name,".xlsx") != NULL) {  
                    (*xlsx_count)++;  
                    fprintf(csv_file,"%s,%s\n",file_name,file_path);  
                } else if (strstr(file_name,".htm") != NULL) {  
                    (*htm_count)++;  
                    fprintf(csv_file,"%s,%s\n",file_name,file_path);  
                } else if (strstr(file_name,".html") != NULL) {  
                    (*html_count)++;  
                    fprintf(csv_file,"%s,%s\n",file_name,file_path);  
                } else if (strstr(file_name,".jpg") != NULL) {  
                    (*jpg_count)++;} else if (strstr(file_name,".jpg") != NULL) {  
                    (*jpg_count)++;  
                    fprintf(csv_file,"%s,%s\n",file_name,file_path);  
                } 
            } 
        } 
        closedir(dir); 
    // } else { 
    //     printf("\nERROR: ");
    //     perror("");
    //     printf("FILE: ");
    //     printf(dir_path);
    //     // exit(EXIT_FAILURE); 
    // } 
//     } else {
//     if (errno == EACCES) {
//         printf("ERROR: Permission denied when attempting to open directory %s\n", dir_path);
//     } else {
//         printf("ERROR: Could not open directory %s\n", dir_path);
//         perror("");
//     }
// }
    } else {
    printf("ERROR: Could not open directory %s: ", dir_path);
    perror("");
    }
} 
 
int main() {  
    setlocale(LC_ALL,""); 
 
    char dir_path[1024];  
    printf("Enter the directory path: ");  
    fgets(dir_path,sizeof(dir_path),stdin);  
    dir_path[strcspn(dir_path,"\n")] = 0;  
     
    FILE *csv_file = fopen("output.csv", "w");  
    fprintf(csv_file,"File Name;File Path\n");  
     
    int pdf_count = 0;  
    int doc_count = 0;  
    int txt_count = 0;  
    int docx_count = 0;  
    int png_count = 0;  
    int jpeg_count = 0;  
    int xls_count = 0;  
    int xlsx_count = 0;  
    int htm_count = 0;  
    int html_count = 0;  
    int jpg_count = 0;  
    
    printf("\nSTARTING MAIN FUNCTION\n");
    process_directory(dir_path,csv_file,&pdf_count,&doc_count,&txt_count,&docx_count,&png_count,&jpeg_count,&xls_count,&xlsx_count,&htm_count,&html_count,&jpg_count); 

    fclose(csv_file); 

    printf("\nWRITING TO FILE");
    FILE *txt_file = fopen("output.txt", "w"); 
    fprintf(txt_file,"pdf: %d\n", pdf_count); 
    fprintf(txt_file,"doc: %d\n", doc_count); 
    fprintf(txt_file,"txt: %d\n", txt_count); 
    fprintf(txt_file,"docx: %d\n", docx_count); 
    fprintf(txt_file,"png: %d\n", png_count); 
    fprintf(txt_file,"jpeg: %d\n", jpeg_count); 
    fprintf(txt_file,"xls: %d\n", xls_count); 
    fprintf(txt_file,"xlsx: %d\n", xlsx_count); 
    fprintf(txt_file,"htm: %d\n", htm_count); 
    fprintf(txt_file,"html: %d\n", html_count); 
    fprintf(txt_file,"jpg: %d\n", jpg_count); 

    fclose(txt_file); 
    printf("\nDONE!\n");
    return 0; 
}