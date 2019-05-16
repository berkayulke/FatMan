#define MAXBUCKETS 100
#include"dataset.h"
#include<stdio.h>
#include<stdlib.h>

//Küçükten büyüğe sırala
void insertion_sort(int *array, int size){
  for (int i = 1; i < size; ++i) {
    /* bu iterasyonda ilgilenilen eleman: pivot */
    int pivot = array[i];
    int j;
    for (j = i; j > 0; --j) {
      /* dogru yeri bulana kadar kaydirma */
      if (pivot < array[j - 1]) {
        array[j] = array[j - 1];
      } else break;
    }
    array[j] = pivot;
  }
}
//Aldığı string dizisini alfabetik sıraya dizer
//BUNU DİREKT KULLANMA İLK ELEMAN LİSTENİN BOYU
void sort_char(char** array, int size){
    int i,j;
    for ( i = 0; i < size; i++)
    {
        for ( j = 0; j < size-1; j++)
        {
            if (alphabetic_order(array[j],array[j+1])==2)
            {
                char* temp=malloc(sizeof(array[j]));
                strcpy(temp,array[j]);
                strcpy(array[j],array[j+1]);
                strcpy(array[j+1],temp);
                free(temp);
            }
            
        }
        
    }
    
}

//Verilen evin hash değerini hesaplar
int hash_compute(House house){
    return (house.id%MAXBUCKETS);
}
//Verilen sayı dizideyse 1 döndürür
int is_in_array(int* list,int value,int size_of_array){
    for (int i = 0; i < size_of_array; i++)
    {
        if (value == list[i])
        {
            return 1;
        }
    }
    return 0;
}

//Verilen string dizideyse 1 döndürür
int is_in_array_string(char** list,char* string,int size_of_array){
    for (int i = 0; i < size_of_array; i++)
    {
        if (!list[i])
        {
            continue;
        }
        
        int value = strcmp(list[i],string);
        if (value==0)
        {
            return 1;
        }
    }
    return 0;
}

int size_of_list(List_house*head){
    int size=0;
    List_house*t=head;
    while (t)
    {
        size++;
        t=t->next;
    }
    return size;
}

//Verilen iki metinden hangisi alfabede öndeyse onun değerini(1 veya 2) döndürür. 0 döndürürse 2 string aynıdır.
int alphabetic_order(char* first,char* second){
    if (!strcmp(first,second))return 0;
    char* c1=malloc(sizeof(char));
    char* c2=malloc(sizeof(char));
    char* f1 = c1;
    char* f2=c2;
    strcpy(c1,first);
    strcpy(c2,second);

    while (*c1!='\0' && *c2!='\0')
    {
        if (*c1 < *c2)
        {
            free(f1);
            free(f2);
            return 1;
        }
        else if(*c2 < *c1)
        {
            free(f1);
            free(f2);
            return 2;
        }
        c1++;
        c2++;
    }
    if (*c1=='\0')
    {
        free(f1);
        free(f2);
        return 1;
    }
    else 
    {
        free(f1);
        free(f2);
        return 2;
    }
}

//Verilen evi kopyalayıp diğerinin üstüne yazar
void copy_house(House* source,House* destination){
    destination->id=source->id;
    destination->kitchenqual=source->kitchenqual;
    destination->lotarea=source->lotarea;
    char* new_neigborhood = malloc(sizeof(source->neighborhood));
    destination->neighborhood=new_neigborhood;
    strcpy(destination->neighborhood,source->neighborhood);
    destination->overallcond=source->overallcond;
    destination->overallqual=source->overallqual;
    destination->saleprice=source->saleprice;
    char* new_street = malloc(sizeof(source->street));
    destination->street = new_street;
    strcpy(destination->street,source->street);
    destination->yearbuilt=source->yearbuilt;
}

//İlk atamaları yapılmış ve malloc ile oluşturulmuş bir hash tablosu döndürür
List_house** create_hash(){
    List_house** head = malloc(MAXBUCKETS*sizeof(List_house*));
    for (int i = 0; i < MAXBUCKETS; i++)
    {
        head[i]=NULL;
    }
    if (head == NULL)
    {
        printf("ne alaka abi");
    }
    
    return head;
}

//Verilen formatlı string'i House değişkenine atar
void read_house(char* text,House* house,int x){
    House* h = malloc(sizeof(House));
    h->street = malloc(sizeof(char));
    h->neighborhood = malloc(sizeof(char));
    if (x)//Listede saleprice bilgisi varsa
    {
        char** dizi=malloc(sizeof(char));
        char** for_free = dizi;
        char* array[9];
        char* kitcqual=malloc(2*sizeof(char));
        char* kitcqual_for_free = kitcqual;
        array[0]= __strtok_r(text,",",dizi);
        for (int i = 1; i < 9; i++)
        {
            array[i] = __strtok_r(*dizi,",",dizi);
        }
        h->id = atoi(array[0]);
        h->lotarea = atoi(array[1]);
        strcpy(h->street,array[2]);
        h->saleprice = atoi(array[3]);
        strcpy(h->neighborhood,array[4]);
        h->yearbuilt=atoi(array[5]);
        h->overallqual=atoi(array[6]);
        h->overallcond = atoi(array[7]);
        strcpy(kitcqual,array[8]);

        if (strcmp("Ex",kitcqual)==0)
        {
          h->kitchenqual=5;
        }
        else if (strcmp("Gd",kitcqual)==0)
        {
          h->kitchenqual=4;
        }
        else if (strcmp("TA",kitcqual)==0)
        {
          h->kitchenqual=3;
        }
        else if (strcmp("Fa",kitcqual)==0)
        {
          h->kitchenqual=2;
        }
        else if (strcmp("Po",kitcqual)==0)
        {
          h->kitchenqual=1;

        }
        else
        {
          printf("\nBROO BI SORUN VAR!!\n");
          h->kitchenqual=0;
        }
        free(kitcqual_for_free);
        copy_house(h,house);
        free(h->neighborhood);
        free(h->street);
        free(h);
        free(for_free);
        return; 
    }
    else{//Listede saleprice bilgisi yoksaa
        char** dizi=malloc(sizeof(char));
        char** for_free = dizi;
        char* array[8];
        char* kitcqual=malloc(2*sizeof(char));
        char* kitcqual_for_free = kitcqual;
        array[0]= __strtok_r(text,",",dizi);
        for (int i = 1; i < 8; i++)
        {
            array[i] = __strtok_r(*dizi,",",dizi);
        }
        h->id = atoi(array[0]);
        h->lotarea = atoi(array[1]);
        strcpy(h->street,array[2]);
        h->saleprice=0;// atoi(array[3]);
        strcpy(h->neighborhood,array[3]);
        h->yearbuilt=atoi(array[4]);
        h->overallqual=atoi(array[5]);
        h->overallcond = atoi(array[6]);
        strcpy(kitcqual,array[7]);

        if (strcmp("Ex",kitcqual)==0)
        {
          h->kitchenqual=5;
        }
        else if (strcmp("Gd",kitcqual)==0)
        {
          h->kitchenqual=4;
        }
        else if (strcmp("TA",kitcqual)==0)
        {
          h->kitchenqual=3;
        }
        else if (strcmp("Fa",kitcqual)==0)
        {
          h->kitchenqual=2;
        }
        else if (strcmp("Gd",kitcqual)==0)
        {
          h->kitchenqual=1;

        }
        else
        {
          printf("\nBROO BI SORUN VAR!!\n");
          h->kitchenqual=0;
        }
        free(kitcqual_for_free);
        copy_house(h,house);
        free(h);
        free(for_free);
    }
}

/*Aldığı formatlı dosyadaki her satırı okuyup hash_table'a ekler
*Okuduğu veri sayısını geri döndürür.
*Listenin fiyat bilgisi varsa x=1, yoksa x=0 ile çağırılmalıdır.
*/
int read_house_data(FILE* file,List_house** hash_table,int x){
    int i =0;
    char* ignore = malloc(100*sizeof(char));
    fscanf(file,"%s\n",ignore);
    free(ignore);
    while (!feof(file))
    {
      House* temp_house = malloc(sizeof(House));
      char* current_text= malloc(100*sizeof(char));
      
      fscanf(file,"%s\n",current_text);
      read_house(current_text,temp_house,x);
      hash_add(hash_table,*temp_house);
      free(temp_house);
      free(current_text);
      i++;
    }
    return i;
}

//Aldığı evi ekrana basar
void print_house (House house){
    printf("\nID: %d\nLotarea: %d\nStreet: %s\nSaleprice: %d\nNeighbodhood:%s\nBuilt Year: %d\nOver All Quality: %d\nOver All Condition: %d\nKitchen Quality: %d",
    house.id,house.lotarea,house.street,house.saleprice,house.neighborhood,
    house.yearbuilt,house.overallqual,house.overallcond,house.kitchenqual);
    printf("\n--------------------\n");
}
//Aldığı listedeki tüm evleri ekrana basar
void print_list(List_house* head){
    List_house* temp = head;
    while (temp)
    {
        print_house(temp->house);
        temp = temp->next;
    }
}
//Aldığı hashteki tüm evleri ekrana basar Test için kullanılabilir
void print_hash(List_house** head){
    int hash = 0;
    for (hash = 0; hash < MAXBUCKETS; hash++)
    {
        List_house* temp_head = head[hash];
        if (!temp_head)
        {
            continue;
        }
        print_list(temp_head);
    }
    
}
//Verilen house'u listeye ekler, hash_add için gereklidir.
List_house* list_add(List_house* head, House house){
    List_house* new_head = malloc(sizeof(List_house));
    copy_house(&house,&(new_head->house));
    new_head->next = head;
    return new_head;
}
//Verilen house'u hash'e ekler
void hash_add(List_house** head, House house){
    int hash = hash_compute(house);
    head[hash] = list_add(head[hash],house); 
}
//Hash'i temizler
void hash_clean(List_house** head){
    for (int i = 0; i < MAXBUCKETS; i++)
    {
        List_house* t_head = head[i];
        if (t_head)
        {
            list_clean(t_head);
        }
    }
    free(head);
}
//Linked list'i temizler
void list_clean(List_house* head){
    List_house* prev=head;
    List_house* t_head = head->next;
    while(t_head)
    {
        free(prev);
        prev = t_head;
        t_head=t_head->next;
    }
    free(prev);
}

//Verilen hash'teki en yüksek fiyatlı 10 evi LinkedList olarak döndürür
List_house* top_10_houses(List_house** head){
    int i = 0,j = 0;
    int current_max=0,current_id=0,counter=0;
    int top_ids[10];
    List_house* list_top = malloc(sizeof(List_house));
    list_top->next=NULL;

    for (i = 0; i < 10; i++)top_ids[i]=-1;
    
    for (j = 0; j < 10; j++)
    {   
        current_max=0;
        for ( i = 0; i < MAXBUCKETS; i++)
        {
            List_house* temp_head = head[i];
            while (temp_head)
            {

                if (current_max<temp_head->house.saleprice && !is_in_array(top_ids,temp_head->house.id,10))
                {
                    current_max = temp_head->house.saleprice;
                    current_id = temp_head->house.id;
                }
                
                temp_head=temp_head->next;
            }
        }
        top_ids[j]=current_id;
    }
   
    for (i = 9; i >=0; i--)
    {
        list_top = list_add(list_top,get_house_byid(head,top_ids[i]));
    }
    List_house* return_pointer = list_top;
    for ( i = 0; i < 9; i++)
    {
        list_top = list_top->next;
    }
    list_top->next=NULL;
    return return_pointer;
    
}

//Verilen id ile eşleşen evi döndürür
//Eger eşleşen ev yoksa id değeri -1 olan bir ev döndürür.
House get_house_byid(List_house** head,int id){
    int hash = id%MAXBUCKETS;

    List_house* temp_head = head[hash];
    while (temp_head)
    {
        if (temp_head->house.id == id)
        {
            return temp_head->house;
        }
        temp_head = temp_head->next;
    }
    House n;
    n.id = -1;
    return n;
}
//Verilen ev ile aynı neighborhood'daki evlerin hash'ini döndürür
List_house** get_neighborhoods(List_house** head,House house){
    List_house** new_head = create_hash();
    for (int i = 0; i < MAXBUCKETS; i++)
    {
        List_house* temp_head = head[i];
        while (temp_head)
        {
            int result = strcmp(temp_head->house.neighborhood,house.neighborhood);
            if (!result)
            {
                hash_add(new_head,temp_head->house);
            }
            temp_head= temp_head->next;
        }
    }
    return new_head;
}

//İlk elemanı dizi boyun olan tüm int kriterleri döndürür
//overallqual ve overallcond arama yöntemiyle çalışmıyor realloc invalid size hatasi
int* get_criter_list_int(List_house** head,char* criter){
    if (!strcmp("lotarea",criter))
    {
        int* criter_list = malloc(sizeof(int));
        criter_list[0] = 0;
        int list_size = 1;
        
        //tüm loot areaların oldugu bir dizi aç, sırasız ekle
        for (int i = 0; i < MAXBUCKETS; i++)
        {
            List_house* temp_head = head[i];
            while (temp_head)
            {
                if (!is_in_array(criter_list ,temp_head->house.lotarea,list_size))
                {   
                    list_size++;
                    criter_list = realloc(criter_list,list_size*sizeof(int));
                    criter_list[list_size-1]=temp_head->house.lotarea;
                }
                temp_head=temp_head->next;
            }   
        }
        insertion_sort(criter_list,list_size);
        criter_list[0]=list_size;
        return criter_list;
    }
    else if (!strcmp("yearbuilt",criter))
    {
        int* criter_list = malloc(sizeof(int));
        criter_list[0]=0;
        int list_size = 1;
        //tüm loot areaların oldugu bir dizi aç, sırasız ekle
        for (int i = 0; i < MAXBUCKETS; i++)
        {
            List_house* temp_head = head[i];
            while (temp_head)
            {
                if (!is_in_array(criter_list ,temp_head->house.yearbuilt,list_size))
                {   
                    list_size++;
                    criter_list = realloc(criter_list,list_size*sizeof(int));
                    criter_list[list_size-1]=temp_head->house.yearbuilt;
                }
                temp_head=temp_head->next;
            }   
        }
        insertion_sort(criter_list,list_size);
        criter_list[0]=list_size;
        return criter_list;
    }
    else if (!strcmp("saleprice",criter))
    {
        int* criter_list = malloc(sizeof(int));
        criter_list[0]=0;
        int list_size = 0;
        //tüm loot areaların oldugu bir dizi aç, sırasız ekle
        for (int i = 0; i < MAXBUCKETS; i++)
        {
            List_house* temp_head = head[i];
            while (temp_head)
            {
                if (!is_in_array(criter_list ,temp_head->house.saleprice,list_size))
                {   
                    list_size++;
                    criter_list = realloc(criter_list,list_size*sizeof(int));
                    criter_list[list_size]=temp_head->house.saleprice;
                }
                temp_head=temp_head->next;
            }   
        }
        insertion_sort(criter_list,list_size);
        criter_list[0]=list_size;
        return criter_list;
    }
    else if (!strcmp("overallqual",criter))
    {
        int* criter_list=malloc(11*sizeof(int));
        for (int i = 1; i < 11; i++)
        {
            criter_list[i]=i;
        }
        criter_list[0]=11;
        
        return criter_list;
    }
    else if (!strcmp("overallcond",criter))
    {
        int* criter_list=malloc(10*sizeof(int));
        for (int i = 1; i < 10; i++)
        {
            criter_list[i]=i;
        }
        criter_list[0]=10;
        return criter_list;
    }
    else if (!strcmp("kitchenqual",criter))
    {
        int* criter_list=malloc(6*sizeof(int));
        for (int i = 1; i < 6; i++)
        {
            criter_list[i]=i;
        }
        criter_list[0]=6;
        return criter_list;
    }
    return NULL;
}
//ilk elemanı dizi boyu olan tüm string kriterleri döndürür
char** get_criter_list_char(List_house** head,char* criter){
    if (!strcmp(criter,"street"))
    {
        char** criter = malloc(sizeof(char*));
        int list_size = 1;
        for (int i = 0; i < MAXBUCKETS; i++)
            {
                List_house* temp_head = head[i];
                while (temp_head)
                {
                    if (!is_in_array_string(criter,temp_head->house.street,list_size))
                    {   
                        list_size++;
                        criter=realloc(criter,list_size*sizeof(char*));
                        char* new_char = malloc(sizeof(temp_head->house.street));
                        strcpy(new_char,temp_head->house.street);
                        criter[list_size-1]=new_char;
                    }
                    temp_head=temp_head->next;
                }   
        }
        criter[0]=list_size;
        char **temp = &criter[1];
        sort_char(temp,list_size-1);
        return criter;
    }
    else if (!strcmp(criter,"neighborhood"))
    {
        char** criter = malloc(sizeof(char*));
        int list_size = 1;
        for (int i = 0; i < MAXBUCKETS; i++)
            {
                List_house* temp_head = head[i];
                while (temp_head)
                {
                    if (!is_in_array_string(criter,temp_head->house.neighborhood,list_size))
                    {   
                        list_size++;
                        criter=realloc(criter,list_size*sizeof(char*));
                        char* new_char = malloc(sizeof(temp_head->house.neighborhood));
                        strcpy(new_char,temp_head->house.neighborhood);
                        criter[list_size-1]=new_char;
                    }
                    temp_head=temp_head->next;
                }   
        }
        criter[0]=list_size;
        char **temp = &criter[1];
        sort_char(temp,list_size-1);
        return criter;
    }
    return NULL;
}

//ilk elemanı dizinin boyu olan ortalamalar dizisi döndürür
float* mean_sale_prices(List_house** head,char* criter){
    if (!strcmp("lotarea",criter))
    {
        int* criter_list = get_criter_list_int(head,criter);
        int list_size = criter_list[0];
        float* means = malloc((list_size+1)*sizeof(float));
        //her farklı lotarea degeri icin bir dizi
        means[0]= (float) list_size;
        for (int i = 1; i < list_size+1; i++)
        {
            means[i]=0.0;
            int current_criter = criter_list[i];
            int current_sum = 0;
            int counter = 0;
            //tüm hash'te gez
            for (int j = 0; j < MAXBUCKETS; j++)
            {
                List_house* temp_head = head[j];
                while (temp_head)
                {
                    if (current_criter == temp_head->house.lotarea)
                    {
                        counter++;
                        current_sum += temp_head->house.saleprice;
                    }

                    temp_head=temp_head->next;
                }

            }
            means[i] =((float)current_sum) / ((float)counter);
        }
        return means;
    }
    else if (!strcmp("yearbuilt",criter))
    {
        int* criter_list = get_criter_list_int(head,criter);
        int list_size = criter_list[0];
        float* means = malloc((list_size+1)*sizeof(float));
        //her farklı lotarea degeri icin bir dizi
        means[0]= (float) list_size;
        for (int i = 1; i < list_size+1; i++)
        {
            means[i]=0.0;
            int current_criter = criter_list[i];
            int current_sum = 0;
            int counter = 0;
            //tüm hash'te gez
            for (int j = 0; j < MAXBUCKETS; j++)
            {
                List_house* temp_head = head[j];
                while (temp_head)
                {
                    if (current_criter == temp_head->house.yearbuilt)
                    {
                        counter++;
                        current_sum += temp_head->house.saleprice;
                    }

                    temp_head=temp_head->next;
                }

            }
            means[i] =((float)current_sum) / ((float)counter);
        }
        return means;
    }
    else if (!strcmp("overallqual",criter))
    {
        int* criter_list = get_criter_list_int(head,criter);
        int list_size = criter_list[0];
        float* means = malloc((list_size+1)*sizeof(float));
        //her farklı lotarea degeri icin bir dizi
        means[0]= (float) list_size;
        for (int i = 1; i < list_size+1; i++)
        {
            means[i]=0.0;
            int current_criter = criter_list[i];
            int current_sum = 0;
            int counter = 0;
            //tüm hash'te gez
            for (int j = 0; j < MAXBUCKETS; j++)
            {
                List_house* temp_head = head[j];
                while (temp_head)
                {
                    if (current_criter == temp_head->house.overallqual)
                    {
                        counter++;
                        current_sum += temp_head->house.saleprice;
                    }

                    temp_head=temp_head->next;
                }

            }
            means[i] =((float)current_sum) / ((float)counter);
        }
        return means;
    }
    else if (!strcmp("overallcond",criter))
    {
        int* criter_list = get_criter_list_int(head,criter);
        int list_size = criter_list[0];
        float* means = malloc((list_size+1)*sizeof(float));
        //her farklı lotarea degeri icin bir dizi
        means[0]= (float) list_size;
        for (int i = 1; i < list_size+1; i++)
        {
            means[i]=0.0;
            int current_criter = criter_list[i];
            int current_sum = 0;
            int counter = 0;
            //tüm hash'te gez
            for (int j = 0; j < MAXBUCKETS; j++)
            {
                List_house* temp_head = head[j];
                while (temp_head)
                {
                    if (current_criter == temp_head->house.overallcond)
                    {
                        counter++;
                        current_sum += temp_head->house.saleprice;
                    }

                    temp_head=temp_head->next;
                }

            }
            means[i] =((float)current_sum) / ((float)counter);
        }
        return means;
    }
    else if (!strcmp("kitchenqual",criter))
    {
        int* criter_list = get_criter_list_int(head,criter);
        int list_size = criter_list[0];
        float* means = malloc((list_size+1)*sizeof(float));
        //her farklı lotarea degeri icin bir dizi
        means[0]= (float) list_size;
        for (int i = 1; i < list_size+1; i++)
        {
            means[i]=0.0;
            int current_criter = criter_list[i];
            int current_sum = 0;
            int counter = 0;
            //tüm hash'te gez
            for (int j = 0; j < MAXBUCKETS; j++)
            {
                List_house* temp_head = head[j];
                while (temp_head)
                {
                    if (current_criter == temp_head->house.kitchenqual)
                    {
                        counter++;
                        current_sum += temp_head->house.saleprice;
                    }

                    temp_head=temp_head->next;
                }

            }
            means[i] =((float)current_sum) / ((float)counter);
        }
        return means;
    }
    else if (!strcmp("street",criter))
    {
        char** criter = NULL;
        int list_size = 0;
        for (int i = 0; i < MAXBUCKETS; i++)
            {
                List_house* temp_head = head[i];
                while (temp_head)
                {
                    if (!is_in_array_string(criter,temp_head->house.street,list_size))
                    {   
                        list_size++;
                        criter=realloc(criter,list_size*sizeof(char*));
                        char* new_char = malloc(sizeof(temp_head->house.street));
                        strcpy(new_char,temp_head->house.street);
                        criter[list_size-1]=new_char;
                    }
                    temp_head=temp_head->next;
                }   
        }
        //Bu noktada criter listende 2 sokak da var.
        
        float* means = malloc((list_size+1)*sizeof(float));
        means[0]=(float)list_size;
        //her farklı lotarea degeri icin bir dizi
        for (int i = 1; i < list_size+1; i++)
        {
            means[i]=0.0;
            char* current_street = malloc(sizeof(criter[i-1]));
            strcpy(current_street,criter[i-1]);
            int current_sum = 0;
            int counter = 0;
            //tüm hash'te gez
            for (int j = 0; j < MAXBUCKETS; j++)
            {
                List_house* temp_head = head[j];
                while (temp_head)
                {
                    if (!strcmp(temp_head->house.street,current_street))
                    {
                        counter++;
                        current_sum += temp_head->house.saleprice;
                    }

                    temp_head=temp_head->next;
                }

            }
            means[i] =((float)current_sum) / ((float)counter);
        }
        return means;
    }
    else if (!strcmp("neighborhood",criter))
    {
        char** criter = NULL;
        int list_size = 0;
        for (int i = 0; i < MAXBUCKETS; i++)
            {
                List_house* temp_head = head[i];
                while (temp_head)
                {
                    if (!is_in_array_string(criter,temp_head->house.neighborhood,list_size))
                    {   
                        list_size++;
                        criter=realloc(criter,list_size*sizeof(char*));
                        char* new_char = malloc(sizeof(temp_head->house.neighborhood));
                        strcpy(new_char,temp_head->house.neighborhood);
                        criter[list_size-1]=new_char;
                    }
                    temp_head=temp_head->next;
                }   
        }
        //Bu noktada criter listende 2 sokak da var.
        
        float* means = malloc((list_size+1)*sizeof(float));
        means[0]=(float)list_size;
        //her farklı lotarea degeri icin bir dizi
        for (int i = 1; i < list_size+1; i++)
        {
            means[i]=0.0;
            char* current_street = malloc(sizeof(criter[i-1]));
            strcpy(current_street,criter[i-1]);
            int current_sum = 0;
            int counter = 0;
            //tüm hash'te gez
            for (int j = 0; j < MAXBUCKETS; j++)
            {
                List_house* temp_head = head[j];
                while (temp_head)
                {
                    if (!strcmp(temp_head->house.neighborhood,current_street))
                    {
                        counter++;
                        current_sum += temp_head->house.saleprice;
                    }

                    temp_head=temp_head->next;
                }

            }
            means[i] =((float)current_sum) / ((float)counter);
        }
        return means;
    }
    else
    {
        return NULL;
    }
}

//Aldığı hash tablosunu kritere göre sıralayıp linked_list'e yazar
List_house* sort_all_houses(List_house** head,char* criter){

    List_house* sort = malloc(sizeof(List_house));//ilk halini NULL yapınca seg fault veriyor
    sort->next=NULL;
    int sorun = 1;
    for (int i = 0; i < MAXBUCKETS; i++)
    {
        List_house* t_head = head[i];
        while (t_head)
        {
            if (sorun)
            {
                copy_house(&(t_head->house),&(sort->house));
                sorun=0;
                continue;
            }
            sort = list_add(sort,t_head->house);
            t_head=t_head->next;
        }
    }
    merge_sort_list(&sort,criter);
    return sort;
}
//Dizideki elemanları dosyaya yazar, yazdığı eleman sayısı döndürür.
int save_sorted_houses(FILE* file,List_house** head,char* criter){
    
    int count=0;
    List_house* asil_liste = sort_all_houses(head,criter);
    while (asil_liste)
    {
        House house = asil_liste->house;
        fprintf(file,"\n*********\nID: %d\nLotarea: %d\nStreet: %s\nSaleprice: %d\nNeighbodhood:%s\nBuilt Year: %d\nOver All Quality: %d\nOver All Condition: %d\nKitchen Quality: %d",
        house.id,house.lotarea,house.street,house.saleprice,house.neighborhood,
        house.yearbuilt,house.overallqual,house.overallcond,house.kitchenqual);
        asil_liste = asil_liste->next;
        count++;
    }
    fclose(file);
    return count;
}

//Aldığı iki listeyi sıralı tek bir liste halinde döndürür
List_house* merge(List_house* left, List_house* right,char* criter){
    if (left==NULL)return right;

    else if (!right)return left;

    if (!strcmp(criter,"lotarea"))
    {
        List_house* new_head = NULL;

        if (left->house.lotarea > right->house.lotarea)
        {
            new_head = left;
            new_head->next = merge(left->next,right,criter);
        }
        else
        {
            new_head = right;
            new_head->next = merge(left,right->next,criter);
        }
        return new_head;
    }
    else if (!strcmp(criter,"yearbuilt"))
    {
        List_house* new_head = NULL;

        if (left->house.yearbuilt > right->house.yearbuilt)
        {
            new_head = left;
            new_head->next = merge(left->next,right,criter);
        }
        else
        {
            new_head = right;
            new_head->next = merge(left,right->next,criter);
        }
        return new_head;
    }
    else if (!strcmp(criter,"overallqual"))
    {
        List_house* new_head = NULL;

        if (left->house.overallqual > right->house.overallqual)
        {
            new_head = left;
            new_head->next = merge(left->next,right,criter);
        }
        else
        {
            new_head = right;
            new_head->next = merge(left,right->next,criter);
        }
        return new_head;
    }
    else if (!strcmp(criter,"overallcond"))
    {
        List_house* new_head = NULL;

        if (left->house.overallcond > right->house.overallcond)
        {
            new_head = left;
            new_head->next = merge(left->next,right,criter);
        }
        else
        {
            new_head = right;
            new_head->next = merge(left,right->next,criter);
        }
        return new_head;
    }
    else if (!strcmp(criter,"kitchenqual"))
    {
        List_house* new_head = NULL;

        if (left->house.kitchenqual > right->house.kitchenqual)
        {
            new_head = left;
            new_head->next = merge(left->next,right,criter);
        }
        else
        {
            new_head = right;
            new_head->next = merge(left,right->next,criter);
        }
        return new_head;   
    }
    else if (!strcmp(criter,"saleprice"))
    {
        List_house* new_head = NULL;

        if (left->house.saleprice > right->house.saleprice)
        {
            new_head = left;
            new_head->next = merge(left->next,right,criter);
        }
        else
        {
            new_head = right;
            new_head->next = merge(left,right->next,criter);
        }
        return new_head;
    }
    else if (!strcmp(criter,"street"))
    {
        List_house* new_head = NULL;
        if (alphabetic_order(right->house.street,left->house.street)==2)
        {
            new_head=left;
            new_head->next = merge(left->next,right,criter);
        }
        else
        {
            new_head=right;
            new_head->next = merge(left,right->next,criter);
        }
    }
    else if (!strcmp(criter,"neighborhood"))
    {
        List_house* new_head = NULL;
        if (alphabetic_order(right->house.neighborhood,left->house.neighborhood)==2)
        {
            new_head=left;
            new_head->next = merge(left->next,right,criter);
        }
        else
        {
            new_head=right;
            new_head->next = merge(left,right->next,criter);
        }
    }
    else
    {
        return NULL;
    }
    
}
//Aldığı listeyi ortadan ikiye böler
void split_list(List_house* source, List_house** left,List_house** right){
    if (!source || !source->next)
    {
        *left = source;
        right = NULL;
        return;
    }
    List_house* slow = source;
    List_house* fast = source->next;

    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        
    }
    *left = source;
    *right = slow->next;
    slow->next = NULL;
}
//Aldığı listeyi criter'e göre sıralar
void merge_sort_list(List_house** head,char* criter){
    if (*head==NULL || (*head)->next == NULL)
    {
        return;
    }
    List_house* left;
    List_house* right;
    split_list(*head,&left,&right);

    merge_sort_list(&left,criter);
    merge_sort_list(&right,criter);
    *head = merge(left,right,criter);    
}
//Verilen hash'teki her listeyi kendi içinde criter'e göre sıralar
void sort_houses(List_house** head, char* criter){
    for (int i = 0; i < MAXBUCKETS; i++)
    {
        merge_sort_list(&head[i],criter);
    }
}