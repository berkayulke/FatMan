#include"models.h"
#include"dataset.h"
#include<stdio.h>
#define lotdiff 800
#define yeardiff 11
#define MAXBUCKETS 100

//Aldığı pointerı istenen özellikteki matrixi yazar
matrix* create_matrix(int satir,int sutun){
  matrix* m = malloc(sizeof(matrix));
  m->satir=satir;
  m->sutun=sutun;
  m->numbers=malloc(satir*sizeof(double*));
  for (int i = 0; i < satir; i++)
  {
    m->numbers[i]=malloc(sutun*sizeof(double));
    for (int j = 0; j < sutun; j++)
    {
      m->numbers[i][j]=0;
    }
  }
  return m;
}
//Matrixi temizler
void free_matrix(matrix* m){
  int satir = m->satir;
  int sutun = m->sutun;
  for (int i = 0; i < satir; i++)
  {
    free(m->numbers[i]);
  }
  free(m->numbers);
  free(m);
}
//Matrixi ekrana basar
void print_matrix(matrix m,char* isim){
  printf("Matix %s:\n",isim);
  for (int i = 0; i < m.satir; i++)
  {
    for (int j = 0; j < m.sutun; j++)
    {
      printf("%.2f ",m.numbers[i][j]);
    }
    printf("\n");
  }
  printf("******\n");
}
//Aldığı matrixin trans pozunu döndürür. Öncesinde create_matrix çağırmaya gerek yok
matrix* get_transpose(matrix source){
  // TODO
  matrix* dest = create_matrix(source.sutun,source.satir);
  if (!dest)
  {
    printf("ULAN BU NE?");
    return NULL;
  }
  
  for (int i = 0; i < source.satir; i++)
  {
    for (int j = 0; j < source.sutun; j++)
    {
      dest->numbers[j][i]=source.numbers[i][j];
    }
  }
  return dest;
}
//Aldığı matrixin tersini döndürür
matrix* get_inverse(matrix m){
  // TODO
  if (m.satir!=m.sutun){
    printf("Bu matrisin tersi alinamaz!\n");
    return &m;
  }
  else if (m.satir!=2)printf("Matris 2x2 değil\n");
    
  matrix* in = create_matrix(2,2);
  in->satir=2;
  in->sutun=2;
  float deter=m.numbers[0][0]*m.numbers[1][1]- m.numbers[0][1]*m.numbers[1][0];
  if (!deter)
  {
    printf("Ula noluyo determinant %.2f\n",deter);
    return &m;
  }
  in->numbers[0][0]=m.numbers[1][1]/deter;
  in->numbers[0][1]=-1*m.numbers[0][1]/deter;
  in->numbers[1][0]=-1*m.numbers[1][0]/deter;
  in->numbers[1][1]=m.numbers[0][0]/deter;
  return in;
}

//2 Matrisi M.N sırasıyla çarpar
matrix* get_multiplication(matrix m, matrix n){
  // TODO
  if (m.sutun!=n.satir)
  {
    printf("Bu matrisler carpilamaz. Ilk matrisi dondurdum\n");
    return &m;
  }
  matrix* res= create_matrix(m.satir,n.sutun);
  for (int i = 0; i < res->satir; i++)
  {
    for (int j = 0; j < res->sutun; j++)
    {
      res->numbers[i][j]=0;
      for (int k = 0; k < m.sutun; k++)
      {
        res->numbers[i][j]+= m.numbers[i][k]*n.numbers[k][j];
      }
    } 
  }
  
  return res;
}

//W Hesabı
matrix* calculate_parameter(matrix X, matrix Y){
  matrix* Xt=get_transpose(X);
  matrix* XtY = get_multiplication(*Xt,Y);
  matrix* XtX = get_multiplication(*Xt,X);
  matrix* XtXin = get_inverse(*XtX);
  matrix* W = get_multiplication(*XtXin,*XtY);
  free_matrix(Xt);
  free_matrix(XtY);
  free_matrix(XtX);
  free_matrix(XtXin);
  return W;
}

float model_by_similarity(List_house** head,House new_house){
  
  float price=0;
  //TODO
  // 1 - Oncelikle ayni komsuluktaki evleri bulun
  List_house** neig= create_hash();
  neig = get_neighborhoods(head,new_house);
  // 2 - Bu evleri lotArea ya gore siralayin
  List_house* sorted_neigs = sort_all_houses(neig,"lotarea");
  hash_clean(neig);
  // 3 - new_house degiskenin lotarea parametresine en
  //  yakin evleri alin, bu evlerin alanlari 
  //  (new_house.lotarea+2000) ve (new_house.lotarea-2000) metrekare arasinda
  //   olabilir.
  List_house* lot_list = malloc(sizeof(List_house));
  lot_list->next=NULL;
  int sorun = 1;
  List_house* t_head = sorted_neigs;
  while (t_head && size_of_list(sorted_neigs)>5)
  {
    
    if (t_head->house.lotarea<= new_house.lotarea+lotdiff && t_head->house.lotarea>=new_house.lotarea-lotdiff)
    {
      if (sorun)
      {
        copy_house(&(t_head->house),&(lot_list->house));
        sorun=0;
        continue;
      }
      else
      {
        lot_list = list_add(lot_list,t_head->house);
      }
    }
    t_head=t_head->next;
  }
  list_clean(sorted_neigs);
  // 4 - Kalan evleri yillarina gore siralayin
  merge_sort_list(&lot_list,"yearbuilt");
  // 5 - new_house degiskenin yearbuilt parametresine en yakin
  // evleri secin, bu evlerin yapim tarihleri
  //  (new_house.yearbuilt+5) ve (new_house-5) arasinda olabilir.
  List_house* year_list=malloc(sizeof(List_house));
  year_list->next=NULL;
  sorun = 1;
  t_head = lot_list;
  while (t_head && size_of_list(lot_list)>1)
  {
    if (t_head->house.yearbuilt <= new_house.yearbuilt+yeardiff && t_head->house.yearbuilt >= new_house.yearbuilt-yeardiff)
    {
      if (sorun)
      {
        copy_house(&(t_head->house),&(year_list->house));
        sorun=0;
        continue;
      }
      
      list_add(year_list,t_head->house);
    }
    t_head=t_head->next;
  }
  list_clean(lot_list);
  // 6 - Ek olarak kaliteye gore secim yapabilirsiniz.
  // 7 - Son elemeden sonra elinizde kalan evlerin fiyat ortalamasini alin
  t_head = year_list;
  int sum=0,coun=0;
  while (t_head)
  {
    sum+=t_head->house.saleprice;
    coun++;
    t_head = t_head->next;
  }
  list_clean(year_list);
  // 8 - Yeni gelen ev icin fiyat degeri bu ortalama olmalidir.
  price = sum/coun;
  printf("TOPLAM EV SAYİSİ : %.2f\n",coun );
  return price;
}

void save_by_similarity(char* file_from,char* file_to,List_house** known_head){
  FILE* file = fopen(file_from,"r");
  List_house** unknown_head=create_hash();
  int read_amount = read_house_data(file,unknown_head,0);
  fclose(file);
  float prediction=0.0;

  List_house* tahminli_liste = malloc(sizeof(List_house));
  tahminli_liste->next=NULL;
  int sorun=1;
  for (int i = 0; i < MAXBUCKETS; i++)
  {
    List_house* t=unknown_head[i];
    while (t)
    {
      if (sorun)
      {
        copy_house(&(t->house),&(tahminli_liste->house));
        prediction = model_by_similarity(known_head,t->house);
        tahminli_liste->house.saleprice = prediction;
        sorun=0;
        t=t->next;
        continue;
      }
      else{

      prediction = model_by_similarity(known_head,t->house);
      tahminli_liste = list_add(tahminli_liste,t->house);
      tahminli_liste->house.saleprice=prediction; 
      t=t->next;
      }
    }  
  }

  FILE* save = fopen(file_to,"w");
  fprintf(save,"Kullanilan Yontem: save_by_similarity\nLotdiff=%d Yeardiff=%d\nID       TAHMIN\n\n",lotdiff,yeardiff);
  
  int ortalama_fark =0,say=0,mevcut_fark=0,birebir=0;
  int eslesme_harici_fark=0;
  while (tahminli_liste)
  {
    House temp = get_house_byid(known_head,tahminli_liste->house.id);
    fprintf(save,"ID:%d   %d\n",tahminli_liste->house.id,tahminli_liste->house.saleprice);//temp.saleprice,abs(temp.saleprice-tahminli_liste->house.saleprice));
    
    tahminli_liste=tahminli_liste->next;
  }
   fclose(save);
}
//x lotarea, y saleprices olacak şekilde doldurur
void create_data_matrices(List_house** head,matrix** X,matrix** Y){
  // TODO
  int size=0;
  List_house* th=NULL;
  for (int i = 0; i < MAXBUCKETS; i++)
  {
    th = head[i];
    while (th)
    {
      size++;
      th=th->next;
    }
    
  }
  
  *X=create_matrix(size,2);
  *Y=create_matrix(size,1);
  int counter=0;
  for (int i = 0; i < MAXBUCKETS; i++)
  {
      th= head[i];
      while (th)
      {
        (*X)->numbers[counter][0]=1;
        (*X)->numbers[counter][1]=(double)th->house.lotarea;
        (*Y)->numbers[counter][0]=(double)th->house.saleprice;
        counter++;
        th=th->next;
      }
  }

}
//Aldığı dosya ve W matrisi ile fiyat tahminleri matrisini döndürür
matrix* make_prediction(char* filename,matrix* W){
  // TODO
  // 1 - filename olarak verilen test verisini oku,
  //   yeni houses dizisi olustur
  List_house** hash = create_hash();
  FILE* file = fopen(filename,"r");
  int read_amount = read_house_data(file,hash,0);
  fclose(file);
  // 2 - create_data_matrices kullanarak X ve y matrislerini olustur
  matrix* X=create_matrix(read_amount,2);
  matrix* Y=create_matrix(read_amount,1);
  create_data_matrices(hash,&X,&Y);
  // 3 - Daha onceden hesaplanan W parametresini kullanarak
  //  fiyat tahmini yap, burda yapilmasi gereken
  //  X ve W matrislerinin carpimini bulmak.
  matrix* mul = get_multiplication(*X,*W);
  
  // 4 - Sonuclari bir dosyaya yaz
  //save_by_make_prediction bunu yapıyor.
  return mul;
}
//file_main'den bilinen evleri okur, 
//file_from'dan fiyatsız evleri alır fiyat tahmini yapıp file_to'ya yazar
void save_by_make_prediction(char* file_main,char* file_from,char* file_to){
  //Her seyi bilinen dosyadan oku
  FILE* file = fopen(file_main,"r");
  List_house** known_head = create_hash();
  int read_amount = read_house_data(file,known_head,1);

  //W hesabi
  matrix* X=create_matrix(read_amount,2);
  matrix* Y=create_matrix(read_amount,1);
  create_data_matrices(known_head,&X,&Y);
  matrix* W =calculate_parameter(*X,*Y);
  matrix* sprices = make_prediction(file_from,W);

  //Saleprice'ı bilinmeyen dosyayı oku
  List_house** unknwon_head= create_hash();
  FILE* f=fopen(file_from,"r");
  int r = read_house_data(f,unknwon_head,0);
  fclose(f);
  printf("%s OKUNDU\n",file_from);

  //Yazarken saleprice'ı sprices'tan, Id'yi unknown_head'ten al
  FILE* f2 = fopen(file_to,"w");
  fprintf(f2,"Kullanilan Yontem:Dogrusal Benzerlik\nID  TAHMIN\n\n");
  int mat_coun=0;

  for (int i = 0; i < MAXBUCKETS; i++)
  {
    List_house* thead = unknwon_head[i];
    while (thead)
    {
      fprintf(f2,"%d %.f\n",thead->house.id,sprices->numbers[mat_coun][0]);
      mat_coun++;
      thead=thead->next;
    }
    
  }
}