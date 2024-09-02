#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8;

typedef struct {
  int width;
  int height;
  uint8* pixel;
} Image;

Image* LoadPGM(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if (!file) {
    perror("Erro ao abrir o arquivo");
    return NULL;
  }

  char magic[3];
  int width, height, maxVal;

  if (fscanf(file, "%2s %d %d %d", magic, &width, &height, &maxVal) != 4) {
    fprintf(stderr, "Formato de arquivo PGM inválido.\n");
    fclose(file);
    return NULL;
  }

  // Verifica se o formato é P5 (imagem em tons de cinza) ou P6 (imagem colorida)
  if (strcmp(magic, "P5") != 0 && strcmp(magic, "P6") != 0) {
    fprintf(stderr, "Este exemplo suporta apenas imagens PGM (P5 ou P6).\n");
    fclose(file);
    return NULL;
  }

  // Verifica se o valor máximo de pixel é razoável
  if (maxVal <= 0 || maxVal > 65535) {
    fprintf(stderr, "Valor máximo de pixel fora do intervalo razoável.\n");
    fclose(file);
    return NULL;
  }

  Image* img = malloc(sizeof(Image));
  img->width = width;
  img->height = height;
  img->pixel = malloc(sizeof(uint8) * width * height);

  fread(img->pixel, sizeof(uint8), width * height, file);

  fclose(file);
  return img;
}



// Função para salvar uma imagem em um arquivo PGM
void SavePGM(const char* filename, const Image* img) {
  FILE* file = fopen(filename, "wb");
  if (!file) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  fprintf(file, "P5\n%d %d\n255\n", img->width, img->height);
  fwrite(img->pixel, sizeof(uint8), img->width * img->height, file);

  fclose(file);
}

// Função para liberar a memória alocada para a imagem
void FreeImage(Image* img) {
  free(img->pixel);
  free(img);
}

// Função para aplicar desfoque sem janela
void ImageBlurNoWindow(Image* img) {
  int width = img->width;
  int height = img->height;
  uint8* blurredPixels = malloc(sizeof(uint8) * width * height);

  if (blurredPixels == NULL) {
    // Falha na alocação de memória
    return;
  }

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      double sum = 0.0;
      double weightSum = 0.0;

      for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
          int newX = x + i;
          int newY = y + j;

          if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
            double weight = 1.0;  // Peso uniforme para todos os pixels na vizinhança
            sum += weight * img->pixel[newY * width + newX];
            weightSum += weight;
          }
        }
      }

      // Calcula a média ponderada dos pixels da vizinhança
      blurredPixels[y * width + x] = (uint8)(sum / weightSum + 0.5);
    }
  }

  // Copia os pixels borrados de volta para a imagem original
  memcpy(img->pixel, blurredPixels, sizeof(uint8) * width * height);
  free(blurredPixels);
}


int main() {
  // Carregar uma imagem de exemplo (substitua "exemplo.pgm" pelo caminho da sua imagem)
  Image* img = LoadPGM("original.pgm");
  if (!img) {
    return 1;
  }

  // Aplicar o desfoque à imagem
  ImageBlurNoWindow(img);

  // Salvar a imagem desfocada (substitua "saida.pgm" pelo caminho de saída desejado)
  SavePGM("saida.pgm", img);

  // Liberar a memória alocada para a imagem
  FreeImage(img);

  return 0;
}
