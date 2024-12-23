#include <stdio.h>
#include <string.h>

struct Book{
    char bookID[20];
    char bookName[50];
    char author[50];
    double price;
    char category[30];
};

int n = 0;
struct Book books[100];

void addBooks();

void inputBook(struct Book *b);

void displayBooks();

void insertBookAtPosition();

void removeBookByID();

void updateBookByID();

void sortBooksByPrice(int ascending);

void searchBookByName();

int main(){
    int choice;
    do{
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin sach.\n");
        printf("2. Hien thi thong tin sach.\n");
        printf("3. Them sach vao vi tri.\n");
        printf("4. Xoa sach theo ma sach.\n");
        printf("5. Cap nhat thong tin sach theo ma sach.\n");
        printf("6. Sap xep sach theo gia(tang/giam).\n");
        printf("7. Tim kiem sach theo ten sach.\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                addBooks();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                insertBookAtPosition();
                break;
            case 4:
                removeBookByID();
                break;
            case 5:
                updateBookByID();
                break;
            case 6: {
                int sortChoice;
                do{
                    printf("Nhap 1 de sap xep tang, 2 de sap xep giam: ");
                    scanf("%d", &sortChoice);
                }while(sortChoice != 1 && sortChoice != 2);
                sortBooksByPrice(sortChoice == 1);
                printf("Danh sach sach sau khi sap xep:\n"); 
                displayBooks();
                break;
            }
            case 7:
                searchBookByName();
                break;
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    }while(choice != 8);

    return 0;
}

void addBooks(){
    int num;
    printf("\nNhap so luong sach: ");
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        printf("\nNhap thong tin sach thu %d:\n", i + 1);
        inputBook(&books[n++]);
    }
}

void inputBook(struct Book *b){
    printf("Nhap ma sach: ");
    scanf("%s", b->bookID);
    getchar();

    printf("Nhap ten sach: ");
    fgets(b->bookName, 50, stdin);
    b->bookName[strcspn(b->bookName, "\n")] = 0;

    printf("Nhap tac gia: ");
    fgets(b->author, 50, stdin);
    b->author[strcspn(b->author, "\n")] = 0;

    printf("Nhap gia tien: ");
    scanf("%lf", &b->price);
    getchar();

    printf("Nhap the loai: ");
    fgets(b->category, 30, stdin);
    b->category[strcspn(b->category, "\n")] = 0;
}

void displayBooks(){
    for(int i = 0; i < n; i++){
        printf("\nMa sach: %s, Ten sach: %s, Tac gia: %s, Gia tien: %.2lf, The loai: %s\n",
               books[i].bookID, books[i].bookName, books[i].author, books[i].price, books[i].category);
    }
}

void insertBookAtPosition(){
    int pos;
    struct Book book;
    printf("\nNhap vi tri can them sach: ");
    scanf("%d", &pos);
    if(pos < 0 || pos > n){
        printf("Vi tri khong hop le.\n");
        return;
    }
    printf("\nNhap thong tin sach can them:\n");
    inputBook(&book);
    for(int i = n; i > pos; i--){
        books[i] = books[i - 1];
    }
    books[pos] = book;
    n++;
}

void removeBookByID(){
    char id[20];
    printf("\nNhap ma sach can xoa: ");
    scanf("%s", id);
    int found = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(books[i].bookID, id) == 0){
            found = 1;
            for(int j = i; j < n - 1; j++){
                books[j] = books[j + 1];
            }
            n--;
            printf("Da xoa sach co ma %s\n", id);
            break;
        }
    }
    if(!found){
        printf("\nKhong tim thay sach co ma %s\n", id);
    }
}

void updateBookByID(){
    char id[20];
    printf("\nNhap ma sach can cap nhat: ");
    scanf("%s", id);
    int found = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(books[i].bookID, id) == 0){
            found = 1;
            printf("Nhap thong tin moi cho sach:\n");
            inputBook(&books[i]);
            break;
        }
    }
    if(!found){
        printf("\nKhong tim thay sach co ma %s\n", id);
    }
}

void sortBooksByPrice(int ascending){
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(ascending){
                if(books[j].price > books[j + 1].price){
                    struct Book temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }else{
                if(books[j].price < books[j + 1].price){
                    struct Book temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }
    }
}

void searchBookByName(){
    char name[50];
    printf("\nNhap ten sach can tim: ");
    getchar();
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;
    int found = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(books[i].bookName, name) == 0){
            printf("\nMa sach: %s, Ten sach: %s, Tac gia: %s, Gia tien: %.2lf, The loai: %s\n",
                   books[i].bookID, books[i].bookName, books[i].author, books[i].price, books[i].category);
            found = 1;
            break;
        }
    }
    if(!found){
        printf("\nKhong tim thay sach co ten %s\n", name);
    }
}
