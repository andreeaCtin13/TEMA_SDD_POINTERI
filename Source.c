#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
typedef struct Influencer Influencer;

struct Influencer {
	char* nume;
	int varsta;
	long int nrAbonati;
	int nrPostari;
	int* nrAprecieri;
};

Influencer initializare(const char* nume, int varsta, long int nrAbonati, int nrPostari, int* nrAprecieri) {
	Influencer aux;
	aux.nume = malloc(strlen(nume) + 1);
	strcpy(aux.nume, nume);
	aux.nrAbonati = nrAbonati;
	aux.nrPostari = nrPostari;
	aux.varsta = varsta;
	aux.nrAprecieri = malloc(sizeof(int) * nrPostari);
	for (int i = 0; i < nrPostari; i++)
	{
		aux.nrAprecieri[i] = nrAprecieri[i];
	}
	return aux;
}

void afisareInfluencer(Influencer f) {
	printf("Numele Influencer-ului: %s\n", f.nume);
	printf("Are varsta: %d\n", f.varsta);
	printf("Numarul de abonati: %d\n", f.nrAbonati);
	printf("Numarul de postari: %d\n", f.nrPostari);
	for (int i = 0; i < f.nrPostari; i++) {
		printf("A %d-a postare are %d aprecieri\n", i + 1, f.nrAprecieri[i]);
	}
}

Influencer copiere(Influencer f) {
	Influencer aux;
	aux.nume = malloc(strlen(f.nume) + 1);
	strcpy(aux.nume, f.nume);
	aux.nrPostari = f.nrPostari;
	aux.varsta = f.varsta;
	aux.nrAbonati = f.nrAbonati;
	aux.nrAprecieri = malloc(sizeof(int) * aux.nrPostari);
	for (int i = 0; i < aux.nrPostari; i++) {
		aux.nrAprecieri[i] = f.nrAprecieri[i];
	}
	return aux;
}

Influencer* adaugaInfluencerVector(Influencer* inf, Influencer i, int* nrInf) {
	(*nrInf)++;
	Influencer* aux = malloc(sizeof(Influencer) * (*nrInf));
	for (int i = 0; i < ((*nrInf) - 1); i++) {
		aux[i] = copiere(inf[i]);
	}
	aux[(*nrInf) - 1] = copiere(i);
	return aux;
}

void afisareVectorInfluenceri(Influencer* inf, int nrInf) {
	for (int i = 0; i < nrInf; i++) {
		afisareInfluencer(inf[i]);
		printf("\n\n");
	}
}

Influencer citireFisierInfluencer(FILE* f) {
	Influencer aux;
	if (!f) {
		printf("Introduceti numele fisierului: \n");
		char num[30];
		scanf("%s", num);
		f = fopen(num, "r");
	}
	char buffer[30];
	fscanf(f, "%s", buffer);
	aux.nume = malloc(strlen(buffer) + 1);
	strcpy(aux.nume, buffer);
	fscanf(f, "%d", &aux.nrAbonati);
	fscanf(f, "%d", &aux.varsta);
	fscanf(f, "%d", &aux.nrPostari);
	aux.nrAprecieri = malloc(sizeof(int) * aux.nrPostari);
	for (int i = 0; i < aux.nrPostari; i++) {
		fscanf(f, "%d", &aux.nrAprecieri[i]);
	}
	return aux;
}

Influencer* citireVectorInfluencerFisier(const char* nume, int* nrInf) {
	FILE* f;
	f = fopen(nume, "r");
	Influencer* inf;
	fscanf(f, "%d", nrInf);
	inf = malloc(sizeof(Influencer) * (*nrInf));
	char buffer[30];
	for (int i = 0; i < (*nrInf); i++) {
		inf[i] = citireFisierInfluencer(f);
	}
	return inf;
}

void writeToFileInfluencer(FILE* f, Influencer inf) {
	if (!f) {
		printf("Introduceti numele fisierului: \n");
		char num[30];
		scanf("%s", num);
		f = fopen(num, "w");
	}
	fprintf(f, "%s\n", inf.nume);
	fprintf(f, "%d\n", inf.nrAbonati);
	fprintf(f, "%d\n", inf.varsta);
	fprintf(f, "%d\n", inf.nrPostari);
	for (int i = 0; i < inf.nrPostari; i++) {
		fprintf(f, "%d ", inf.nrAprecieri[i]);
	}
	fprintf(f, "\n");
}

void writeToFileVectorInfluencer(FILE* f, Influencer* inf, int nr) {
	if (!f) {
		char buffer[30];
		printf("Intorduceti numele fisierului din cate cititi vectorul de influenceri: \n");
		scanf("%s", buffer);
		f = fopen(buffer, "w");
	}
	fprintf(f, "%d\n", nr);
	for (int i = 0; i < nr; i++) {
		writeToFileInfluencer(f, inf[i]);
	}
}

Influencer citireTastaturaInfluencer() {
	Influencer aux;
	printf("Introduceti numele influencer-ului: \n");
	char buffer[30];
	scanf("%s", buffer);
	aux.nume = malloc(strlen(buffer) + 1);
	strcpy(aux.nume, buffer);
	printf("Introduceti varsta influencer-ului: \n");
	scanf("%d", &aux.varsta);
	printf("Introduceti numarul de abonati al influencer-ului: \n");
	scanf("%d", &aux.nrAbonati);
	printf("Introduceti numarul de poistari ale influencer-ului: \n");
	scanf("%d", &aux.nrPostari);
	aux.nrAprecieri = malloc(sizeof(int) * aux.nrPostari);
	for (int i = 0; i < aux.nrPostari; i++) {
		printf("Introduceti numarul de aprecieri aferent a %d-a postare:", i + 1);
		scanf("%d", &aux.nrAprecieri[i]);
	}
	return aux;
}

Influencer* citireVectorInfluencerTastatura(int* nr) {
	Influencer* inf;
	printf("Introduceti numarul de influenceri cititi:\n");
	scanf("%d", nr);
	inf = malloc(sizeof(Influencer) * (*nr));
	for (int i = 0; i < (*nr); i++) {
		printf("\nDate referitoare la al %d-lea influencer\n", i + 1);
		inf[i] = citireTastaturaInfluencer();
	}
	return inf;
}


Influencer** createMatrix(Influencer*lista, int **dim, int *nrElem, int *nrLinii) {
	(*nrLinii) = 3;
	Influencer** mat = malloc(sizeof(Influencer *)* (*nrElem));
	int i = 0, k=0;
	(*dim) = malloc(3*sizeof(int*));
	for (int j = 0; j < 3; j++) {
		(*dim)[j] = 0;
	}
	for (int j = 0; j < (*nrElem); j++) {
		if (lista[j].nrPostari == 3) {
			(*dim)[0]++;
		}
		else if (lista[j].nrPostari == 5) {
			(*dim)[1]++;
		}
		else {
			(*dim)[2]++;
		}
	}

	while (i < 3) {
		mat[i] = malloc(sizeof(Influencer) * (*dim)[i]);
		for (int j = 0; j < (*dim)[i]; j++) {
			mat[i][j] = lista[k];
			k++;
		}
		i++;
	}
	return mat;
}

void afisareMatrix(Influencer** matrix, int* dim, int nrLinii) {
	for (int i = 0; i < nrLinii; i++) {
			afisareVectorInfluenceri(matrix[i], dim[i]);
			printf("-------------------------------------\n");
	}
}

Influencer* copiereVectorInfluencer(Influencer* v1, int dim1) {
	Influencer* f = malloc(sizeof(Influencer) * dim1);
	for (int i = 0; i < dim1; i++) {
		f[i]=copiere(v1[i]);
	}
	return f;
}

int calcMax(int* vect, int nr) {
	int max = -1;
	for (int i = 0; i < nr; i++) {
		if (vect[i] > max) {
			max = vect[i];
		}
	}
}

Influencer* concat(Influencer* i1, Influencer* i2, int dim1, int dim2, int* dim3) {
	(*dim3) = dim1 + dim2;
	Influencer* concatenat = malloc((*dim3) * sizeof(Influencer));
	for (int i = 0; i < dim1; i++) {
		concatenat[i]= copiere(i1[i]);
	}
	for (int i = dim1; i < (*dim3); i++) {
		concatenat[i] = copiere(i2[i - dim1]);
	}
	return concatenat;
}

Influencer* selectareNrAbonati(Influencer* f, int nrInf, int *nrNou) {
	(*nrNou) = 0;
	for (int i = 0; i < nrInf; i++) {
		if (f[i].nrAbonati >= 3000) {
			(*nrNou)++;
		}
	}
	Influencer* bombix = malloc(sizeof(Influencer) * (*nrNou));
	int contor = 0;
	for (int i = 0; i < nrInf; i++) {
		if (f[i].nrAbonati >= 3000) {
			bombix[contor] = copiere(f[i]);
			contor++;
		}
	}
	return bombix;
}

Influencer** sortMatrix(Influencer** matrix, int **nrCol, int nrLinii) {
	int maxCol = calcMax(*nrCol, nrLinii);
	Influencer** nou = malloc(sizeof(Influencer*) * (nrLinii));
	for (int i = 0; i < nrLinii; i++) {
		nou[i] = malloc(sizeof(Influencer) * (*nrCol)[i]);
	}
	printf("%d", maxCol);
	int* dim = malloc(sizeof(int) * nrLinii);
	int contor = 0;
	for (int i = 1; i < maxCol&&contor!=nrLinii; i++) {
		for (int j = 0; j < nrLinii; j++) {
			if ((*nrCol)[j] == i) {
				nou[contor] = copiereVectorInfluencer(matrix[j], (*nrCol)[j]);
				dim[contor] = (*nrCol)[j];
				contor++;
			}
		}
	}
	for (int i = 0; i < nrLinii; i++) {
		(*nrCol)[i] = dim[i];
	}
	return nou;
}

int main() {
	//Influencer f;
	int* nrAprecieri = malloc(sizeof(int) * 3);
	nrAprecieri[0] = 8000;
	nrAprecieri[1] = 7000;
	nrAprecieri[2] = 6000;
	//f = initializare("HAHA", 14, 14000, 3, nrAprecieri);
	//afisareInfluencer(f);
	//Influencer fe = copiere(f);
	//afisareInfluencer(fe);

	//printf("\n------------------------------------------------------\n");
	Influencer i1, i2, i3, i4;
	i1 = initializare("HAHA1", 14, 14000, 3, nrAprecieri);
	i2 = initializare("HAHA2", 14, 14000, 3, nrAprecieri);
	i3 = initializare("HAHA3", 14, 14000, 3, nrAprecieri);
	i4 = initializare("HAHA4", 14, 14000, 3, nrAprecieri);
	Influencer i5;
	i5 = initializare("HAHA5", 14, 14000, 3, nrAprecieri);
	Influencer* vector = malloc(sizeof(Influencer) * 4);
	vector[0] = i1;
	vector[1] = i2;
	vector[2] = i3;
	vector[3] = i4;
	int nrElem = 4;
	////vector = adaugaInfluencerVector(vector, i5, &nrElem);
	////afisareVectorInfluenceri(vector, nrElem);

	//FILE* file = NULL;
	//Influencer chitra;
	////chitra = citireFisierInfluencer(file);
	////afisareInfluencer(chitra);
	//Influencer nebuniaLuiSalam;
	////nebuniaLuiSalam = citireFisierInfluencer(file);
	////afisareInfluencer(nebuniaLuiSalam);

	////fac shallow copy

	Influencer* array;
	int nrInf;
	array = citireVectorInfluencerFisier("InfluencerVector.txt", &nrInf);
	afisareVectorInfluenceri(array, nrInf);
	//printf("\n----------------------Afisare Vectori din  fisier----------------------------\n");
	//afisareVectorInfluenceri(array, nrInf);

	//FILE* scriu = NULL;
	//writeToFileInfluencer(scriu, i1);
	//writeToFileVectorInfluencer(scriu, vector, nrElem);
	////Influencer nou = citireTastaturaInfluencer();
	////afisareInfluencer(nou);
	//int nrEl;
	////Influencer* nouVector = citireVectorInfluencerTastatura(&nrEl);
	////afisareVectorInfluenceri(nouVector, nrEl);
	/*int nrInf1, nrLinii;
	Influencer* vector1 = citireVectorInfluencerFisier("InfluencerVector.txt", &nrInf1);

	afisareVectorInfluenceri(vector, nrInf);
	Influencer** bou;
	int* dim;
	bou = createMatrix(vector1, &dim, &nrInf1, &nrLinii);
	bou = sortMatrix(bou, &dim, nrInf1);
	afisareMatrix(bou, dim, nrLinii);
	int nrNouu;
	Influencer* nouuu = concat(vector, array, nrElem, nrInf, &nrNouu);
	afisareVectorInfluenceri(nouuu, nrNouu);
	int nrSelect = 0;
	Influencer* vip=selectareNrAbonati(array, nrInf, &nrSelect);
	afisareVectorInfluenceri(vip, nrSelect);*/
	//afisareVectorInfluenceri(vector1, nrInf);
	//printf("\n\n\nPLANG MOR MA IMPUSC\n\n\n");
	//afisareVectorInfluenceri(vector2, nrInf);

	//bou = sorteazaMatrix(bou, &dim, 3);
	//afisareMatrix(bou, dim, 3);
}