#include"dataset.h"
#include"models.h"


int main(int argc,char * argv[]){
  if (argc==1)
  {
    printf("Lutfen dosya giriniz\n");
    return 1;
  }
  
  int cevap=7;
  while(cevap!=0){
    List_house** head = create_hash();
    printf("Emlak Programina Hosgeldiniz!\n");
    printf("Yapmak istediginiz islemi seciniz\n");
    printf("1 - Evleri listele\n");
    printf("2 - ID degeri verilen evi goster\n");
    printf("3 - ID degeri verilen evin komsu evlerini bul \n");
    printf("4 - Kritere gore satis fiyati ortalamalarini goster\n");
    printf("5 - En yuksek fiyata sahip ilk 10 evi goster\n");
    printf("6 - Sirali ev listesini kaydet\n");
    printf("7 - Dogrusal denklem yontemiyle fiyat tahmini yap\n");
    printf("8 - Benzerlik yontemiyle fiyat tahmini yap (Onerilendir)\n");
    printf("Programdan cikmak icin 0 a basiniz.\n");
    scanf("%d",&cevap);
    
    if(cevap==1){
      printf("Ev listesi \n");
      // TODO
      // Butun evleri listele
      List_house** head = create_hash();
      FILE* file = fopen(argv[1],"r");
      int read_amount = read_house_data(file,head,1);
      print_hash(head);
      hash_clean(head);
      rewind(file);
      fclose(file);
    }
    else if(cevap==2){
      List_house** head = create_hash();
      FILE* file = fopen(argv[1],"r");
      int read_amount = read_house_data(file,head,1);
      printf("ID degeri verilen ev \n");
     // TODO
     // print_house ile tek evi goster
     // get_house_byid cagrisi yap
     printf("Lutfen istediginiz evin ID degerini giriniz:\n");
     int id=0;
     scanf("%d",&id);
     House wanted = get_house_byid(head,id);
     if (wanted.id!=-1)
     {
       print_house(wanted);
     }
     else
     {
       printf("Bu id degerine sahip bir ev bulunamadi\n"); 
     }
     
     hash_clean(head);
     rewind(file);
     fclose(file);
    }
    else if(cevap==3){
      printf("Komsu evler \n");
      List_house** head = create_hash();
      FILE* file = fopen(argv[1],"r");
      int read_amount = read_house_data(file,head,1);
      // TODO
      // get_neighborhoods 
      printf("Lutfen komsulari listelenecek evin ID degerini giriniz:\n");
      int id=0;
      scanf("%d",&id);
      List_house** neigbs = create_hash();
      House neig = get_house_byid(head,id);
      if (neig.id == -1)
      {
        printf("Komsu evler bulunamadi\n");
        continue;
      }
      else
      {
        neigbs = get_neighborhoods(head,neig);
        print_hash(neigbs);
        hash_clean(head);
        rewind(file);
        fclose(file);
      }
      
    }
    else if(cevap==4){
      List_house** head = create_hash();
      FILE* file = fopen(argv[1],"r");
      int read_amount = read_house_data(file,head,1);
       printf("Ortalama satislar\n");
       // TODO
       // mean_sale_prices
       printf("Lutfen kriterinizi giriniz:\n");
       char criter[100];
       scanf("%s",criter);
       if (!strcmp(criter,"street")||!strcmp(criter,"neighborhood"))
       {
         char** criters = get_criter_list_char(head,criter);
         float* means = mean_sale_prices(head,criter);
         for (int i = 1; i < (int)criters[0]; i++)
         {
           printf("%s=%s ortalamasi: %.2f\n",criter,criters[i],means[i]);
         }
       }
      if(!strcmp(criter,"lotarea") || !strcmp(criter,"yearbuilt") || !strcmp(criter,"overallqual")||!strcmp(criter,"overallcond")|| !strcmp(criter,"kitchenqual"))
       {
         int* criters = get_criter_list_int(head,criter);
         
         float* means = mean_sale_prices(head,criter);
         for (int i = 1; i < means[0]; i++)
         {
           printf("%s=%d ortalamasi: %.2f\n",criter,criters[i],means[i]);
         }
         
       }
       else
       {
         printf("Gecersiz bir kriter girdiniz\n*********\n");
         printf("Gecerli parametreler:\n lotarea  yearbuilt ovevrallqual  overallcond kitchenqual street  neighborhood\n**********\n");
       }
      hash_clean(head);
      rewind(file);
      fclose(file);
       
    }
    else if(cevap==5){
      List_house** head = create_hash();
      FILE* file = fopen(argv[1],"r");
      int read_amount = read_house_data(file,head,1);
       printf("En yuksek fiyatli evler\n");
       // TODO 
       List_house* list = top_10_houses(head);
       print_list(list);
       hash_clean(head);
       list_clean(list);
       rewind(file);
      fclose(file);
    }
    else if(cevap==6){
      List_house** head = create_hash();
      FILE* file = fopen(argv[1],"r");
      int read_amount = read_house_data(file,head,1);
       printf("Sirali evler\n");
       // TODO
       char criter[100],file_name[100];
       printf("Lutfen kriterinizi giriniz:\n");
       scanf("%s",criter);

       if (strcmp(criter,"street") && strcmp(criter,"neighborhood") && strcmp(criter,"lotarea") && strcmp(criter,"yearbuilt") && strcmp(criter,"overallqual") && strcmp(criter,"overallcond") && strcmp(criter,"kitchenqual"))
       {
         printf("Gecersiz bir kriter girdiniz\n*********\n");
         printf("Gecerli parametreler:\n lotarea  yearbuilt ovevrallqual  overallcond kitchenqual street  neighborhood\n**********\n");
         continue;
       }
       printf("Dosyanizin adini giriniz:\n");
       scanf("%s",file_name);
       FILE* save = fopen(file_name,"w");
       fprintf(save,"Siralama Kriteri: %s\n",criter);
       save_sorted_houses(save,head,criter);
       hash_clean(head);
       rewind(file);
       fclose(file);
    }
    else if(cevap==7){ 
        List_house** head = create_hash();
        FILE* file = fopen(argv[1],"r");
        int read_amount = read_house_data(file,head,1);
        printf("Okunan ev sayisi=%d\n",read_amount);
        rewind(file);
        printf("Fiyat tahmini yap\n");

        printf("Tahmin edilecek dosyanin adini giriniz:\n");
        char file_from[256];
        char file_to[256];
        scanf( "%s" , file_from );
        printf("Kayit dosyasinin ismini giriniz:\n");
        scanf( "%s" , file_to );
        //Saleprice'ı bilinmeyen dosyayı oku ve unknown_head'e at
        //Kaydedilecek dosyayi aç
        //FILE* save = fopen(argv[1],"r");
        save_by_make_prediction(argv[1],file_from,file_to);
        //rewind(save);
        printf("DOSYANIN KAYDOLMASI ICIN PROGRAMI KAPATINIZ\n");
        hash_clean(head);
        fclose(file);
    }
    else if(cevap==8)
    {
      printf("Tahmin edilecek dosyanin adini giriniz:\n");
      char file_from[256];
      char file_to[256];
      scanf( "%s" , file_from );
      printf("Kayit dosyasinin ismini giriniz:\n");
      scanf( "%s" , file_to );
      FILE* f= fopen(argv[1],"r");
      List_house** head = create_hash();
      int read_amount = read_house_data(f,head,1);
      save_by_similarity(file_from,file_to,head);
    }
  }
  printf("Programadan cikiliyor\n");
  return 0; 
}