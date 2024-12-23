#include <stdio.h>
#include <string.h>

struct Product{
    char productID[20];
    char productName[50];
    double importPrice;
    double salePrice;
    int quantity;
};

struct Product products[100];
int n = 0;
double revenue = 0;

void addProducts();

void inputProduct(struct Product *p);

void displayProducts();

void importProduct();

void updateProductByID();

void sortProductsByPrice(int ascending);

void searchProductByName();

void sellProduct();

void displayRevenue();

int main(){
    int choice;
    do{
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham.\n");
        printf("2. Hien thi danh sach san pham.\n");
        printf("3. Nhap san pham.\n");
        printf("4. Cap nhat thong tin san pham.\n");
        printf("5. Sap xep san pham theo gia(tang/giam).\n");
        printf("6. Tim kiem san pham.\n");
        printf("7. Ban san pham (co the nhap so luong can ban).\n");
        printf("8. Doanh thu hien tai.\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                addProducts();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                importProduct();
                break;
            case 4:
                updateProductByID();
                break;
            case 5: {
                int sortChoice;
                do{
                    printf("Nhap 1 de sap xep tang, 2 de sap xep giam: ");
                    scanf("%d", &sortChoice);
                }while(sortChoice != 1 && sortChoice != 2);
                sortProductsByPrice(sortChoice == 1);
                printf("Danh sach san pham sau khi sap xep:\n");
                displayProducts();
                break;
            }
            case 6:
                searchProductByName();
                break;
            case 7:
                sellProduct();
                break;
            case 8:
                displayRevenue();
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    }while(choice != 9);

    return 0;
}

void addProducts(){
    int num;
    printf("\nNhap so luong san pham: ");
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        printf("\nNhap thong tin san pham thu %d:\n", i + 1);
        inputProduct(&products[n++]);
        revenue -= products[n - 1].quantity * products[n - 1].importPrice;
    }
}

void inputProduct(struct Product *p){
    printf("Nhap ma san pham: ");
    scanf("%s", p->productID);
    getchar();

    printf("Nhap ten san pham: ");
    fgets(p->productName, 50, stdin);
    p->productName[strcspn(p->productName, "\n")] = 0;

    printf("Nhap gia nhap: ");
    scanf("%lf", &p->importPrice);

    printf("Nhap gia ban: ");
    scanf("%lf", &p->salePrice);

    printf("Nhap so luong: ");
    scanf("%d", &p->quantity);
}

void displayProducts(){
    for(int i = 0; i < n; i++){
        printf("\nMa san pham: %s, Ten san pham: %s, Gia nhap: %.2lf, Gia ban: %.2lf, So luong: %d\n",
               products[i].productID, products[i].productName, products[i].importPrice, products[i].salePrice, products[i].quantity);
    }
}

void importProduct(){
    char id[20];
    int quantity;
    printf("\nNhap ma san pham can nhap: ");
    scanf("%s", id);
    printf("Nhap so luong can nhap: ");
    scanf("%d", &quantity);

    int found = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(products[i].productID, id) == 0){
            found = 1;
            products[i].quantity += quantity;
            revenue -= quantity * products[i].importPrice;
            break;
        }
    }

    if(!found){
        printf("San pham khong ton tai.\n");
    }
}

void updateProductByID(){
    char id[20];
    printf("\nNhap ma san pham can cap nhat: ");
    scanf("%s", id);

    int found = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(products[i].productID, id) == 0){
            found = 1;
            printf("Nhap thong tin moi cho san pham:\n");
            inputProduct(&products[i]);
            break;
        }
    }

    if(!found){
        printf("Khong tim thay san pham co ma %s\n", id);
    }
}

void sortProductsByPrice(int ascending){
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(ascending){
                if(products[j].salePrice > products[j + 1].salePrice){
                    struct Product temp = products[j];
                    products[j] = products[j + 1];
                    products[j + 1] = temp;
                }
            }else{
                if(products[j].salePrice < products[j + 1].salePrice){
                    struct Product temp = products[j];
                    products[j] = products[j + 1];
                    products[j + 1] = temp;
                }
            }
        }
    }
}

void searchProductByName(){
    char name[50];
    printf("Nhap ten san pham can tim: ");
    getchar();
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    int found = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(products[i].productName, name) == 0){
            printf("\nMa san pham: %s, Ten san pham: %s, Gia nhap: %.2lf, Gia ban: %.2lf, So luong: %d\n",
                   products[i].productID, products[i].productName, products[i].importPrice, products[i].salePrice, products[i].quantity);
            found = 1;
            break;
        }
    }

    if(!found){
        printf("Khong tim thay san pham co ten %s\n", name);
    }
}

void sellProduct(){
    char id[20];
    int quantity;
    printf("\nNhap ma san pham can ban: ");
    scanf("%s", id);
    printf("Nhap so luong can ban: ");
    scanf("%d", &quantity);

    int found = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(products[i].productID, id) == 0){
            found = 1;
            if(products[i].quantity < quantity){
                printf("Khong con du hang.\n");
            }else if(products[i].quantity == 0){
                printf("Het hang.\n");
            }else{
                products[i].quantity -= quantity;
                revenue += quantity * products[i].salePrice;
                printf("Da ban %d san pham co ma %s\n", quantity, id);
            }
            break;
        }
    }

    if(!found){
        printf("Khong tim thay san pham co ma %s\n", id);
    }
}

void displayRevenue(){
    printf("Doanh thu hien tai: %.2lf\n", revenue);
}
