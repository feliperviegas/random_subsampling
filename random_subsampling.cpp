#include "random_subsampling.h"

void shuffle(std::vector<std::string> &a) {
    int idx = a.size(); //se eu não colocar esse -1 da falha se segmentação
    while (idx > 0) {
      int rnd_idx = (int)Utils::random(0.0, (double)idx);
      idx--;
//    std::cout<<"idx "<<idx<<" rnd_idx "<<rnd_idx<<std::endl;
      std::string tmp = a[idx];
      a[idx] = a[rnd_idx];
      a[rnd_idx] = tmp;
    }
} 

void read_input(const char* filename, std::vector<std::string> &vetor){
  std::ifstream file(filename);
  std::string lines;
  while(std::getline(file, lines)){
   vetor.push_back(lines);
  }
}

void gera_teste_treino(std::vector<std::string> &vetor, float p){
  int lines = static_cast<int>(p * static_cast<double>(vetor.size()));
  std::ofstream teste("teste.dat");
  std::ofstream treino("treino.dat");
  for(int i=0;i<vetor.size();i++){
    if (i < lines) teste << vetor[i] << std::endl;
    else treino << vetor[i] << std::endl;
  }
  teste.close();
  treino.close();
}


int main(int argc, char** argv) {

  float percent = 1;
  char *data_file = NULL;
  int seed = time(NULL);
  int iterator =1;  
  int opt;
 
  while ((opt = getopt (argc, argv, "d:p:i:")) != -1) {
    switch (opt) {
      case 'd': data_file = optarg; break;
      case 'p': percent = atof(optarg); break;		//Porcentagem para teste
      case 'i': iterator = atoi(optarg); break;
      case '?':
        if ((optopt == 'd'))
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
      default:
        std::cerr << "USAGE: " << argv[0] << " -l <val> -i <val>" << std::endl;
        abort ();
    }
  }
  //seed = seed + iterator;
  srand48(iterator); 
  std::vector<std::string> vet;
  read_input(data_file, vet);
  shuffle(vet);
  gera_teste_treino(vet, percent);
  return 0;
}
