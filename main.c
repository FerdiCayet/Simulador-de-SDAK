#include <stdio.h>    
#include <stdlib.h>    
#include <locale.h>    
#include <windows.h>  
#include <string.h>    
#include <time.h>      
#include <dirent.h>    
#include <sys/stat.h>  

#define MAX_STRING_SIZE 200

// Definição da estrutura para armazenar um par de login e senha.
struct Acesso {
    char login[50];
    char senha[50];
};

// Definição da estrutura para armazenar os dados do veículo.
struct Veiculo {
    char data[MAX_STRING_SIZE];
    char hora[MAX_STRING_SIZE];
    char nome[MAX_STRING_SIZE];
    char placa[MAX_STRING_SIZE];
    char marca[MAX_STRING_SIZE];
    char modelo[MAX_STRING_SIZE];
    char cor[MAX_STRING_SIZE];
    char observacao[MAX_STRING_SIZE];
    char municipio[MAX_STRING_SIZE];
    char cnh[MAX_STRING_SIZE];
    char uf[MAX_STRING_SIZE];
    char local[MAX_STRING_SIZE];
    char numero_local[MAX_STRING_SIZE];
    char bairro[MAX_STRING_SIZE];
};

// Função para fazer comparação de strings (case-insensitive).
char* strcasestr_custom(const char* haystack, const char* needle) {
    while (*haystack) {
        const char* h = haystack;
        const char* n = needle;  

        while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n))) {
            h++;
            n++;
        }

        if (!*n) {
            return (char*)haystack;
        }

        haystack++;
    }

    return NULL;
}

// Função para limpar a tela do console no ambiente Windows
void limparTela() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
   
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);

    SetConsoleCursorPosition(hConsole, coordScreen);
}

// Função para autenticar o usuário
int autenticarUsuario() {
    char login[4] = "ssp";
    char ssp[4];

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    SetConsoleTitle("Digite ssp na tela");
    scanf("%s", ssp);
    if (strcmp(login, ssp) == 0) {
        limparTela();
        SetConsoleTitle("SDAK - Sistema de Cadastro de Veículos");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("Acesso autorizado!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        Sleep(1500);
        limparTela();

        int acessoAutorizado;
        acessoAutorizado = acessarSistemas();

        if (!acessoAutorizado) {
            printf("É necessário possuir um sistema de acesso para utilizar o programa.\n");
            getch();
            exit(0);
        }
        return 1;
    } else {
        SetConsoleTitle("ERRO");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 76);
        printf("ACESSO NEGADO!\nErro\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        exit(EXIT_FAILURE);
    }
}

// Função para cadastrar novo acesso de sistemas
void cadastrarAcesso() {
    struct Acesso novoAcesso;
    char resposta;
    int i = 0;
    FILE *arquivo;

    printf("Digite o novo login: ");
    scanf("%s", novoAcesso.login);
    printf("Digite a nova senha: ");
    //scanf("%s", novoAcesso.senha);
   
    while (1) {
        char c = getch();

        if (c == 13) {
            novoAcesso.senha[i] = '\0';
            break;
        } else if (c == 8 && i > 0) {
            printf("\b \b");
            i--;
        } else if (i < 20 - 1) {
            novoAcesso.senha[i] = c;
            printf("*");
            i++;
        }
    }

    arquivo = fopen("acesso.txt", "a");

    if (arquivo == NULL) {
        Sleep(1500);
        perror("\nErro ao abrir o arquivo de acesso!\n");
        return;
    }

    fprintf(arquivo, "%s %s\n", novoAcesso.login, novoAcesso.senha);
    fclose(arquivo);

    printf("Novo acesso cadastrado com sucesso!\n");
    Sleep(1500);
    limparTela();
    acessarSistemas();
}

// Função para verificar o acesso e contar tentativas
int acessarSistemas() {
    struct Acesso acesso;
    char inputLogin[50];
    char inputSenha[50];
    int acessoAutorizado = 0;
    int tentativas = 0;
    FILE *arquivo;

    arquivo = fopen("acesso.txt", "r");

    if (arquivo == NULL) {
        char resposta;
        int c;
        do {
            printf("Arquivo de acesso nao encontrado. Deseja criar um novo arquivo de acesso? (S/N): ");
            c = getchar();
        } while (c != EOF && c != '\n');

        resposta = getchar();

        if (resposta == 'S' || resposta == 's') {
            arquivo = fopen("acesso.txt", "w");

            if (arquivo == NULL) {
                perror("Erro ao criar o arquivo de acesso!\n");
                Sleep(1500);
                return 0;
            } else {
                printf("Arquivo de acesso criado com sucesso.\n");
                Sleep(1500);
                limparTela();
                cadastrarAcesso();
                fclose(arquivo);
                return 1;
            }
        } else {
            fclose(arquivo);
            return 0;
        }
    }

    while (1) {
        printf("Digite o login (ou 'q' para sair): ");
        scanf("%s", inputLogin);

        if (strcmp(inputLogin, "Q") == 0 || strcmp(inputLogin, "q") == 0) {
            printf("Encerrando o programa...\n");
            fclose(arquivo);
            Sleep(1500);
            exit(0);
        }

        printf("Digite a senha: ");
        //scanf("%s", inputSenha);

        int i = 0;

        while (1) {
            char c = getch();

            if (c == 13) {
                inputSenha[i] = '\0';
                break;
            } else if (c == 8 && i > 0) {
                printf("\b \b");
                i--;
            } else if (i < 20) {
                inputSenha[i] = c;
                printf("*");
                i++;
            }
        }

        fseek(arquivo, 0, SEEK_SET);

        while (fscanf(arquivo, "%s %s", acesso.login, acesso.senha) == 2) {
            if (strcmp(inputLogin, acesso.login) == 0 && strcmp(inputSenha, acesso.senha) == 0) {
                acessoAutorizado = 1;
                break;
            }
        }

        if (acessoAutorizado) {
            limparTela();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            printf("Acesso autorizado! Bem-vindo, %s.\n", inputLogin);
            Sleep(2000);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            break;
        } else {
            printf("Acesso Negado! Verifique o login e a senha.\n");
            tentativas++;

            if (tentativas >= 3) {
                printf("Limite de tentativas excedido. Saindo do programa.\n");
                fclose(arquivo);
                exit(1);
            }
        }
    }

    fclose(arquivo);
    return acessoAutorizado;
}

// Função para adicionar um novo registro
void adicionarRegistro() {
    struct Veiculo veiculo;
    char placaArquivo[30];

    printf("Digite a data (no formato AAAA-MM-DD): ");
    fgets(veiculo.data, sizeof(veiculo.data), stdin);
    veiculo.data[strcspn(veiculo.data, "\n")] = '\0';

    printf("Digite a hora (no formato HH:MM): ");
    fgets(veiculo.hora, sizeof(veiculo.hora), stdin);
    veiculo.hora[strcspn(veiculo.hora, "\n")] = '\0';

    printf("Digite o nome: ");
    fgets(veiculo.nome, sizeof(veiculo.nome), stdin);
    veiculo.nome[strcspn(veiculo.nome, "\n")] = '\0';

    printf("Digite a placa: ");
    fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
    veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';

    printf("Digite a marca: ");
    fgets(veiculo.marca, sizeof(veiculo.marca), stdin);
    veiculo.marca[strcspn(veiculo.marca, "\n")] = '\0';

    printf("Digite o modelo: ");
    fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';

    printf("Digite a cor: ");
    fgets(veiculo.cor, sizeof(veiculo.cor), stdin);
    veiculo.cor[strcspn(veiculo.cor, "\n")] = '\0';

    printf("Digite a observação: ");
    fgets(veiculo.observacao, sizeof(veiculo.observacao), stdin);
    veiculo.observacao[strcspn(veiculo.observacao, "\n")] = '\0';

    printf("Digite o município: ");
    fgets(veiculo.municipio, sizeof(veiculo.municipio), stdin);
    veiculo.municipio[strcspn(veiculo.municipio, "\n")] = '\0';

    printf("Digite o número da CNH: ");
    fgets(veiculo.cnh, sizeof(veiculo.cnh), stdin);
    veiculo.cnh[strcspn(veiculo.cnh, "\n")] = '\0';

    printf("Digite a UF: ");
    fgets(veiculo.uf, sizeof(veiculo.uf), stdin);
    veiculo.uf[strcspn(veiculo.uf, "\n")] = '\0';

    printf("Digite o local: ");
    fgets(veiculo.local, sizeof(veiculo.local), stdin);
    veiculo.local[strcspn(veiculo.local, "\n")] = '\0';

    printf("Digite o número do local: ");
    fgets(veiculo.numero_local, sizeof(veiculo.numero_local), stdin);
    veiculo.numero_local[strcspn(veiculo.numero_local, "\n")] = '\0';

    printf("Digite o bairro: ");
    fgets(veiculo.bairro, sizeof(veiculo.bairro), stdin);
    veiculo.bairro[strcspn(veiculo.bairro, "\n")] = '\0';

    FILE *arquivo;

    snprintf(placaArquivo, sizeof(placaArquivo), "%s.txt", veiculo.placa);

    arquivo = fopen(placaArquivo, "a");

    if (arquivo == NULL) {
        perror("O arquivo não pode ser aberto.\n");
        Sleep(1300);
        return;
    }

    fprintf(arquivo, "Data e Hora: %s %s\n", veiculo.data, veiculo.hora);
    fprintf(arquivo, "Nome: %s\n", veiculo.nome);
    fprintf(arquivo, "Placa: %s\n", veiculo.placa);
    fprintf(arquivo, "Marca: %s\n", veiculo.marca);
    fprintf(arquivo, "Modelo: %s\n", veiculo.modelo);
    fprintf(arquivo, "Cor: %s\n", veiculo.cor);
    fprintf(arquivo, "Observação: %s\n", veiculo.observacao);
    fprintf(arquivo, "Município: %s\n", veiculo.municipio);
    fprintf(arquivo, "CNH: %s\n", veiculo.cnh);
    fprintf(arquivo, "UF: %s\n", veiculo.uf);
    fprintf(arquivo, "Local: %s\n", veiculo.local);
    fprintf(arquivo, "número do Local: %s\n", veiculo.numero_local);
    fprintf(arquivo, "Bairro: %s", veiculo.bairro);

    fflush(arquivo);
    printf("\nRegistro adicionado com sucesso no arquivo %s.\n", placaArquivo);
    Sleep(2000);
}

// Função para listar registros em um arquivo específico
void listarRegistrosArquivo(const char *nomeArquivo) {
    struct Veiculo veiculo;
    char buffer[2000];

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("O arquivo não existe ou não pode ser aberto.\n");
        Sleep(1500);
        return;
    }

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        if (strstr(buffer, "Data e Hora: ") == buffer) {
            if (sscanf(buffer, "Data e Hora: %s %s", veiculo.data, veiculo.hora) != 2) {
                continue;
            }
           
            if (fgets(veiculo.nome, sizeof(veiculo.nome), arquivo) == NULL ||
                fgets(veiculo.placa, sizeof(veiculo.placa), arquivo) == NULL ||
                fgets(veiculo.marca, sizeof(veiculo.marca), arquivo) == NULL ||
                fgets(veiculo.modelo, sizeof(veiculo.modelo), arquivo) == NULL ||
                fgets(veiculo.cor, sizeof(veiculo.cor), arquivo) == NULL ||
                fgets(veiculo.observacao, sizeof(veiculo.observacao), arquivo) == NULL ||
                fgets(veiculo.municipio, sizeof(veiculo.municipio), arquivo) == NULL ||
                fgets(veiculo.cnh, sizeof(veiculo.cnh), arquivo) == NULL ||
                fgets(veiculo.uf, sizeof(veiculo.uf), arquivo) == NULL ||
                fgets(veiculo.local, sizeof(veiculo.local), arquivo) == NULL ||
                fgets(veiculo.numero_local, sizeof(veiculo.numero_local), arquivo) == NULL ||
                fgets(veiculo.bairro, sizeof(veiculo.bairro), arquivo) == NULL) {
                continue;
            }

            veiculo.nome[strcspn(veiculo.nome, "\n")] = '\0';
            veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';
            veiculo.marca[strcspn(veiculo.marca, "\n")] = '\0';
            veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';
            veiculo.cor[strcspn(veiculo.cor, "\n")] = '\0';
            veiculo.observacao[strcspn(veiculo.observacao, "\n")] = '\0';
            veiculo.municipio[strcspn(veiculo.municipio, "\n")] = '\0';
            veiculo.cnh[strcspn(veiculo.cnh, "\n")] = '\0';
            veiculo.uf[strcspn(veiculo.uf, "\n")] = '\0';
            veiculo.local[strcspn(veiculo.local, "\n")] = '\0';
            veiculo.numero_local[strcspn(veiculo.numero_local, "\n")] = '\0';
            veiculo.bairro[strcspn(veiculo.bairro, "\n")] = '\0';

            printf("Data e Hora: %s %s\n", veiculo.data, veiculo.hora);
            printf("%s\n", veiculo.nome);
            printf("%s\n", veiculo.placa);
            printf("%s\n", veiculo.marca);
            printf("%s\n", veiculo.modelo);
            printf("%s\n", veiculo.cor);
            printf("%s\n", veiculo.observacao);
            printf("%s\n", veiculo.municipio);
            printf("%s\n", veiculo.cnh);
            printf("%s\n", veiculo.uf);
            printf("%s\n", veiculo.local);
            printf("%s\n", veiculo.numero_local);
            printf("%s\n", veiculo.bairro);
            printf("\n_____________________\n\n");
        }
    }
    fclose(arquivo);
}

// Função para listar registros em todos os arquivos com extensão .txt
void listarRegistros() {
    const char *diretorio = ".";
    DIR *dp;
    struct dirent *entry;

    dp = opendir(diretorio);

    if (dp == NULL) {
        perror("opendir");
        Sleep(1500);
        return;
    }

    while ((entry = readdir(dp))) {
        if (strstr(entry->d_name, ".txt") != NULL && strcmp(entry->d_name, "acesso.txt") != 0) {
            printf("Listando registros para arquivo %s:\n\n", entry->d_name);
            listarRegistrosArquivo(entry->d_name);
            printf("\n");
        }
    }

    closedir(dp);
    getch();
}

// Função para buscar e editar um registro
void editarRegistro() {
    struct Veiculo veiculo;
    char placaBusca[20];
    char buffer[2000];
    char nomeArquivo[30];

    char novoNomeArquivo[50];
    int encontrado = 0;

    printf("Digite a placa do veículo que deseja editar (ou digite 'q' para sair): ");
    fgets(placaBusca, sizeof(placaBusca), stdin);
    placaBusca[strcspn(placaBusca, "\n")] = '\0';

    if (placaBusca[0] == 'q') {
        return;
    }

    if (placaBusca[0] == '\0' || placaBusca[0] == ' ') {
        printf("O termo de busca não pode ser vazio.\n");
        Sleep(1500);
        return;
    }

    //strcat(placaBusca, ".txt");

    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", placaBusca);

    FILE *arquivo = fopen(nomeArquivo, "r");

    FILE *tempArquivo = fopen("temp.txt", "w");
    if (tempArquivo == NULL) {
        perror("Erro ao criar arquivo temporário.\n");
        Sleep(1500);
        return;
    }

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        if (strstr(buffer, "Data e Hora: ") == buffer) {
            if (sscanf(buffer, "Data e Hora: %s %s", veiculo.data, veiculo.hora) != 2) {
                continue;
            }
           
            if (fgets(veiculo.nome, sizeof(veiculo.nome), arquivo) == NULL ||
                fgets(veiculo.placa, sizeof(veiculo.placa), arquivo) == NULL ||
                fgets(veiculo.marca, sizeof(veiculo.marca), arquivo) == NULL ||
                fgets(veiculo.modelo, sizeof(veiculo.modelo), arquivo) == NULL ||
                fgets(veiculo.cor, sizeof(veiculo.cor), arquivo) == NULL ||
                fgets(veiculo.observacao, sizeof(veiculo.observacao), arquivo) == NULL ||
                fgets(veiculo.municipio, sizeof(veiculo.municipio), arquivo) == NULL ||
                fgets(veiculo.cnh, sizeof(veiculo.cnh), arquivo) == NULL ||
                fgets(veiculo.uf, sizeof(veiculo.uf), arquivo) == NULL ||
                fgets(veiculo.local, sizeof(veiculo.local), arquivo) == NULL ||
                fgets(veiculo.numero_local, sizeof(veiculo.numero_local), arquivo) == NULL ||
                fgets(veiculo.bairro, sizeof(veiculo.bairro), arquivo) == NULL) {
                continue;
            }

            if (strcmp(veiculo.placa, placaBusca) != 0) {
                encontrado = 1;

                printf("\nRegistro encontrado:\n\n");
                printf("Data e Hora: %s %s\n", veiculo.data, veiculo.hora);
                printf("%s", veiculo.nome);
                printf("%s", veiculo.placa);
                printf("%s", veiculo.marca);
                printf("%s", veiculo.modelo);
                printf("%s", veiculo.cor);
                printf("%s", veiculo.observacao);
                printf("%s", veiculo.municipio);
                printf("%s", veiculo.cnh);
                printf("%s", veiculo.uf);
                printf("%s", veiculo.local);
                printf("%s", veiculo.numero_local);
                printf("%s\n\n");

                char resposta[2];
                printf("Deseja editar este registro? (S/N): ");
                fgets(resposta, sizeof(resposta), stdin);

                if (toupper(resposta[0]) == 'S') {
                    getchar();
                   
                    printf("\nInforme novos dados\n\nDigite a data (no formato AAAA-MM-DD): ");
                    fgets(veiculo.data, sizeof(veiculo.data), stdin);
                    veiculo.data[strcspn(veiculo.data, "\n")] = '\0';

                    printf("Digite a hora (no formato HH:MM): ");
                    fgets(veiculo.hora, sizeof(veiculo.hora), stdin);
                    veiculo.hora[strcspn(veiculo.hora, "\n")] = '\0';

                    printf("Digite o nome: ");
                    fgets(veiculo.nome, sizeof(veiculo.nome), stdin);
                    veiculo.nome[strcspn(veiculo.nome, "\n")] = '\0';

                    printf("Digite a placa: ");
                    fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
                    veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';

                    printf("Digite a marca: ");
                    fgets(veiculo.marca, sizeof(veiculo.marca), stdin);
                    veiculo.marca[strcspn(veiculo.marca, "\n")] = '\0';

                    printf("Digite o modelo: ");
                    fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
                    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';

                    printf("Digite a cor: ");
                    fgets(veiculo.cor, sizeof(veiculo.cor), stdin);
                    veiculo.cor[strcspn(veiculo.cor, "\n")] = '\0';

                    printf("Digite a observação: ");
                    fgets(veiculo.observacao, sizeof(veiculo.observacao), stdin);
                    veiculo.observacao[strcspn(veiculo.observacao, "\n")] = '\0';

                    printf("Digite o município: ");
                    fgets(veiculo.municipio, sizeof(veiculo.municipio), stdin);
                    veiculo.municipio[strcspn(veiculo.municipio, "\n")] = '\0';

                    printf("Digite o número da CNH: ");
                    fgets(veiculo.cnh, sizeof(veiculo.cnh), stdin);
                    veiculo.cnh[strcspn(veiculo.cnh, "\n")] = '\0';

                    printf("Digite a UF: ");
                    fgets(veiculo.uf, sizeof(veiculo.uf), stdin);
                    veiculo.uf[strcspn(veiculo.uf, "\n")] = '\0';

                    printf("Digite o local: ");
                    fgets(veiculo.local, sizeof(veiculo.local), stdin);
                    veiculo.local[strcspn(veiculo.local, "\n")] = '\0';

                    printf("Digite o número do local: ");
                    fgets(veiculo.numero_local, sizeof(veiculo.numero_local), stdin);
                    veiculo.numero_local[strcspn(veiculo.numero_local, "\n")] = '\0';

                    printf("Digite o bairro: ");
                    fgets(veiculo.bairro, sizeof(veiculo.bairro), stdin);
                    veiculo.bairro[strcspn(veiculo.bairro, "\n")] = '\0';

                    fprintf(tempArquivo, "Data e Hora: %s %s\n", veiculo.data, veiculo.hora);
                    fprintf(tempArquivo, "Nome: %s\n", veiculo.nome);
                    fprintf(tempArquivo, "Placa: %s\n", veiculo.placa);
                    fprintf(tempArquivo, "Marca: %s\n", veiculo.marca);
                    fprintf(tempArquivo, "Modelo: %s\n", veiculo.modelo);
                    fprintf(tempArquivo, "Cor: %s\n", veiculo.cor);
                    fprintf(tempArquivo, "Observação: %s\n", veiculo.observacao);
                    fprintf(tempArquivo, "Município: %s\n", veiculo.municipio);
                    fprintf(tempArquivo, "CNH: %s\n", veiculo.cnh);
                    fprintf(tempArquivo, "UF: %s\n", veiculo.uf);
                    fprintf(tempArquivo, "Local: %s\n", veiculo.local);
                    fprintf(tempArquivo, "número do Local: %s\n", veiculo.numero_local);
                    fprintf(tempArquivo, "Bairro: %s\n", veiculo.bairro);

                    printf("\nRegistro editado com sucesso.\n");

                    sprintf(novoNomeArquivo, "%s.txt", veiculo.placa);

                    fflush(tempArquivo);
                    Sleep(1500);

                } else {
                    encontrado = 0;

                    fprintf(tempArquivo, "Data e Hora: %s %s\n", veiculo.data, veiculo.hora);
                    fgets(veiculo.nome, sizeof(veiculo.nome), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.nome);
                    fgets(veiculo.placa, sizeof(veiculo.placa), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.placa);
                    fgets(veiculo.marca, sizeof(veiculo.marca), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.marca);
                    fgets(veiculo.modelo, sizeof(veiculo.modelo), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.modelo);
                    fgets(veiculo.cor, sizeof(veiculo.cor), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.cor);
                    fgets(veiculo.observacao, sizeof(veiculo.observacao), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.observacao);
                    fgets(veiculo.municipio, sizeof(veiculo.municipio), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.municipio);
                    fgets(veiculo.cnh, sizeof(veiculo.cnh), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.cnh);
                    fgets(veiculo.uf, sizeof(veiculo.uf), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.uf);
                    fgets(veiculo.local, sizeof(veiculo.local), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.local);
                    fgets(veiculo.numero_local, sizeof(veiculo.numero_local), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.numero_local);
                    fgets(veiculo.bairro, sizeof(veiculo.bairro), arquivo);
                    fprintf(tempArquivo, "%s", veiculo.bairro);
                }
            }
        } else {
            continue;
        }
    }

    fclose(tempArquivo);
    fclose(arquivo);

    if (encontrado) {
        remove(nomeArquivo);
        rename("temp.txt", novoNomeArquivo);
    } else {
        remove("temp.txt");
        printf("Registro não encontrado.\n");
        Sleep(1500);
    }
}

// Função para apagar um registro
void apagarRegistro() {
    struct Veiculo veiculo;
    char placaBusca[20];
    char nomeArquivo[30];
    int encontrado = 0;

    printf("Digite a placa do veículo que deseja apagar (ou digite 'q' para sair): ");
    fgets(placaBusca, sizeof(placaBusca), stdin);
    placaBusca[strcspn(placaBusca, "\n")] = '\0';

    if (placaBusca[0] == 'q') {
        return;
    }

    if (placaBusca[0] == '\0' || placaBusca[0] == ' ') {
        printf("O termo de busca não pode ser vazio.\n");
        Sleep(1500);
        return;
    }
   
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", placaBusca);

    FILE *arquivo = fopen(nomeArquivo, "r+");
    FILE *tempFile = fopen("temp.txt", "w");

    while (fgets(veiculo.data, sizeof(veiculo.data), arquivo) != NULL) {
        /*if (strstr(veiculo.data, "Data e Hora: ") != veiculo.data) {
            continue;
        }*/
       
        fgets(veiculo.hora, sizeof(veiculo.hora), arquivo);
        fgets(veiculo.nome, sizeof(veiculo.nome), arquivo);
        fgets(veiculo.placa, sizeof(veiculo.placa), arquivo);
        fgets(veiculo.marca, sizeof(veiculo.marca), arquivo);
        fgets(veiculo.modelo, sizeof(veiculo.modelo), arquivo);
        fgets(veiculo.cor, sizeof(veiculo.cor), arquivo);
        fgets(veiculo.observacao, sizeof(veiculo.observacao), arquivo);
        fgets(veiculo.municipio, sizeof(veiculo.municipio), arquivo);
        fgets(veiculo.cnh, sizeof(veiculo.cnh), arquivo);
        fgets(veiculo.uf, sizeof(veiculo.uf), arquivo);
        fgets(veiculo.local, sizeof(veiculo.local), arquivo);
        fgets(veiculo.numero_local, sizeof(veiculo.numero_local), arquivo);
        fgets(veiculo.bairro, sizeof(veiculo.bairro), arquivo);
       
        if (strcmp(veiculo.placa, placaBusca) != 0) {
            encontrado = 1;

            printf("\nRegistro encontrado:\n");
            printf("%s", veiculo.data);
            printf("%s", veiculo.hora);
            printf("%s", veiculo.nome);
            printf("%s", veiculo.placa);
            printf("%s", veiculo.marca);
            printf("%s", veiculo.modelo);
            printf("%s", veiculo.cor);
            printf("%s", veiculo.observacao);
            printf("%s", veiculo.municipio);
            printf("%s", veiculo.cnh);
            printf("%s", veiculo.uf);
            printf("%s", veiculo.local);
            printf("%s", veiculo.numero_local);
            printf("%s\n\n");

            char resposta[2];
            printf("Deseja confirmar a exclusão deste registro? (S/N): ");
            fgets(resposta, sizeof(resposta), stdin);

            if (toupper(resposta[0]) == 'S') {
                remove(nomeArquivo);
                Sleep(1500);
                continue;
            }
        }
    }
   
    fclose(arquivo);
    fclose(tempFile);

    if (!encontrado) {
        printf("Registro não encontrado.\n");
        Sleep(1500);
    }

    remove("temp.txt");
}

// Função para contar registros de hoje
void contarRegistrosHoje() {
    struct tm *today;
    char nomeArquivo[30];
    int contador = 0;
    time_t now;

    time(&now);
    today = localtime(&now);

    char dataAtual[11];
    strftime(dataAtual, sizeof(dataAtual), "%Y-%m-%d", today);

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".txt") != NULL && strcmp(ent->d_name, "acesso.txt") != 0) {
                struct stat st;
                stat(ent->d_name, &st);
                struct tm *fileTime = localtime(&st.st_mtime);

                char fileDate[11];
                strftime(fileDate, sizeof(fileDate), "%Y-%m-%d", fileTime);

                if (strcmp(fileDate, dataAtual) == 0) {
                    printf("Nome do arquivo encontrado: %s\n\n", ent->d_name);
                    printf("A data atual: %s\n", dataAtual);
                    printf("A data de modificação do arquivo: %s\n", fileDate);
                    printf("\n______________________\n\n");
                    contador++;
                }
            }
        }
        closedir(dir);
    }

    printf("\nForam encontrados %d arquivos criados hoje.\n", contador);
    getch();
}

// Função para contar registros em uma data específica do arquivo
void contarRegistrosData() {
    struct tm *today;
    char nomeArquivo[30];
    int contador = 0;
    time_t now;

    time(&now);
    today = localtime(&now);

    char dataBusca[20];
    printf("Digite a data (no formato AAAA-MM-DD) (ou digite 'q' para sair): ");
    fgets(dataBusca, sizeof(dataBusca), stdin);
    dataBusca[strcspn(dataBusca, "\n")] = '\0';

    if (dataBusca[0] == 'q') {
        return;
    }

    if (dataBusca[0] == '\0' || dataBusca[0] == ' ') {
        printf("O termo de busca não pode ser vazio.\n");
        Sleep(1500);
        return;
    }

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(".")) != NULL) {
       
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".txt") != NULL && strcmp(ent->d_name, "acesso.txt") != 0) {
                struct stat st;
                stat(ent->d_name, &st);
                struct tm *fileTime = localtime(&st.st_mtime);

                char fileDate[11];
                strftime(fileDate, sizeof(fileDate), "%Y-%m-%d", fileTime);

                if (strcmp(fileDate, dataBusca) == 0) {
                    printf("Nome do arquivo encontrado: %s\n\n", ent->d_name);
                    printf("A data digitada: %s\n", dataBusca);
                    printf("A data de modificação do arquivo: %s\n", fileDate);
                    printf("\n______________________\n\n");
                    contador++;
                }
            }
        }
        closedir(dir);
    }
   
    printf("\nForam encontrados %d arquivos criados na data %s.\n", contador, dataBusca);
    getch();
}

// Função para pesquisar por placa do veículo
void lerInformacaoPlaca() {
    struct Veiculo veiculo;
    char placaBusca[50];
    char nomeArquivo[30];
    char buffer[2000];
    int encontrado = 0;

    printf("Digite a placa do veículo que deseja pesquisar (ou digite 'q' para sair): ");
    fgets(placaBusca, sizeof(placaBusca), stdin);
    placaBusca[strcspn(placaBusca, "\n")] = '\0';

    if (placaBusca[0] == 'q') {
        return;
    }

    if (placaBusca[0] == '\0' || placaBusca[0] == ' ') {
        printf("O termo de busca não pode ser vazio.\n");
        Sleep(1500);
        return;
    }
   
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", placaBusca);

    FILE *arquivo = fopen(nomeArquivo, "r");

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        if (strstr(buffer, "Data e Hora: ") == buffer) {
            if (sscanf(buffer, "Data e Hora: %s %s", veiculo.data, veiculo.hora) != 2) {
                continue;
            }

            if (fgets(veiculo.nome, sizeof(veiculo.nome), arquivo) == NULL ||
                fgets(veiculo.placa, sizeof(veiculo.placa), arquivo) == NULL ||
                fgets(veiculo.marca, sizeof(veiculo.marca), arquivo) == NULL ||
                fgets(veiculo.modelo, sizeof(veiculo.modelo), arquivo) == NULL ||
                fgets(veiculo.cor, sizeof(veiculo.cor), arquivo) == NULL ||
                fgets(veiculo.observacao, sizeof(veiculo.observacao), arquivo) == NULL ||
                fgets(veiculo.municipio, sizeof(veiculo.municipio), arquivo) == NULL ||
                fgets(veiculo.cnh, sizeof(veiculo.cnh), arquivo) == NULL ||
                fgets(veiculo.uf, sizeof(veiculo.uf), arquivo) == NULL ||
                fgets(veiculo.local, sizeof(veiculo.local), arquivo) == NULL ||
                fgets(veiculo.numero_local, sizeof(veiculo.numero_local), arquivo) == NULL ||
                fgets(veiculo.bairro, sizeof(veiculo.bairro), arquivo) == NULL) {
                continue;
            }

            veiculo.hora[strcspn(veiculo.hora, "\n")] = '\0';
            veiculo.nome[strcspn(veiculo.nome, "\n")] = '\0';
            veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';
            veiculo.marca[strcspn(veiculo.marca, "\n")] = '\0';
            veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';
            veiculo.cor[strcspn(veiculo.cor, "\n")] = '\0';
            veiculo.observacao[strcspn(veiculo.observacao, "\n")] = '\0';
            veiculo.municipio[strcspn(veiculo.municipio, "\n")] = '\0';
            veiculo.cnh[strcspn(veiculo.cnh, "\n")] = '\0';
            veiculo.uf[strcspn(veiculo.uf, "\n")] = '\0';
            veiculo.local[strcspn(veiculo.local, "\n")] = '\0';
            veiculo.numero_local[strcspn(veiculo.numero_local, "\n")] = '\0';
            veiculo.bairro[strcspn(veiculo.bairro, "\n")] = '\0';

            if (strcmp(veiculo.placa, placaBusca) != 0 ){
                encontrado = 1;

                printf("\nRegistro encontrado!\n");
                printf("Data e Hora: %s %s\n", veiculo.data, veiculo.hora);
                printf("%s\n", veiculo.nome);
                printf("%s\n", veiculo.placa);
                printf("%s\n", veiculo.marca);
                printf("%s\n", veiculo.modelo);
                printf("%s\n", veiculo.cor);
                printf("%s\n", veiculo.observacao);
                printf("%s\n", veiculo.municipio);
                printf("%s\n", veiculo.cnh);
                printf("%s\n", veiculo.uf);
                printf("%s\n", veiculo.local);
                printf("%s\n", veiculo.numero_local);
                printf("%s\n", veiculo.bairro);
                printf("___________\n\n");
            }
        }
    }

    if (!encontrado) {
        printf("Nenhum registro encontrado com a placa \"%s\".\n", placaBusca);
    }
    fclose(arquivo);
    getch();
}

// Função para pesquisar históricos
void pesquisarHistoricos() {
    char termoBusca[100];
    char linha[1000];
    int encontrado = 0;
    int linhaAtual = 0;

    while (1) {
        printf("Digite a palavra que deseja pesquisar nos históricos (ou digite 'q' para sair): ");
        fgets(termoBusca, sizeof(termoBusca), stdin);
        termoBusca[strcspn(termoBusca, "\n")] = '\0';

        if (termoBusca[0] == 'q') {
            break;
        }
       
        if (termoBusca[0] == '\0' || termoBusca[0] == ' ') {
            printf("O termo de busca não pode ser vazio.\n");
            Sleep(1500);
            break;
        }

        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(".")) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
               
                if (strstr(ent->d_name, ".txt") != NULL && strcmp(ent->d_name, "acesso.txt") != 0) {


                    FILE *arquivo = fopen(ent->d_name, "r");
                    if (arquivo != NULL) {
                        linhaAtual = 0;


                        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                            linhaAtual++;


                            if (strcasestr_custom(linha, termoBusca) != NULL) {
                                encontrado = 1;
                                printf("Palavra encontrada na linha %d do arquivo %s:\n", linhaAtual, ent->d_name);
                                printf("%s\n", linha);
                            }
                        }
                        fclose(arquivo);
                    }
                }
            }
            closedir(dir);
        }

        if (!encontrado) {
            printf("A palavra '%s' não foi encontrada em nenhum arquivo de histórico.\n", termoBusca);
        } else {
            lerInformacaoPlaca();
            encontrado = 0;
        }
    }
}

// Função executar o menu prinicipal
int main() {
    setlocale(LC_ALL, "");

    int opcao;

    autenticarUsuario();

    while (1) {
        time_t tempoAtual;
        struct tm *tempoInfo;
        char horaString[9];
        char dataString[11];
       
        time(&tempoAtual);
        tempoInfo = localtime(&tempoAtual);
       
        strftime(horaString, sizeof(horaString), "%H:%M:%S", tempoInfo);
        strftime(dataString, sizeof(dataString), "%d/%m/%Y", tempoInfo);
       
        limparTela();
        printf("\n\t\t\t\t\tSISTEMA DE CADASTRO DE VEÍCULOS\n");
        printf("%s\t\t\t\t\tProjeto SDAK\t\t\t\t\t%s\n", horaString, dataString);
        printf("----------------------------------------------------------------------------------------------------------");
        printf("\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("\t   SSSSSSSSSSSSSSS DDDDDDDDDDDDD                  AAA               KKKKKKKKK    KKKKKKK\n");
        printf("\t SS:::::::::::::::SD::::::::::::DDD              A:::A              K:::::::K    K:::::K\n");
        printf("\tS:::::SSSSSS::::::SD:::::::::::::::DD           A:::::A             K:::::::K    K:::::K\n");
        printf("\tS:::::S     SSSSSSSDDD:::::DDDDD:::::D         A:::::::A            K:::::::K   K::::::K\n");
        printf("\tS:::::S              D:::::D    D:::::D       A:::::::::A           KK::::::K  K:::::KKK\n");
        printf("\tS:::::S              D:::::D     D:::::D     A:::::A:::::A            K:::::K K:::::K   \n");
        printf("\t S::::SSSS           D:::::D     D:::::D    A:::::A A:::::A           K::::::K:::::K    \n");
        printf("\t  SS::::::SSSSS      D:::::D     D:::::D   A:::::A   A:::::A          K:::::::::::K     \n");
        printf("\t    SSS::::::::SS    D:::::D     D:::::D  A:::::A     A:::::A         K:::::::::::K     \n");
        printf("\t       SSSSSS::::S   D:::::D     D:::::D A:::::AAAAAAAAA:::::A        K::::::K:::::K    \n");
        printf("\t            S:::::S  D:::::D     D:::::DA:::::::::::::::::::::A       K:::::K K:::::K   \n");
        printf("\t            S:::::S  D:::::D    D:::::DA:::::AAAAAAAAAAAAA:::::A    KK::::::K  K:::::KKK\n");
        printf("\tSSSSSSS     S:::::SDDD:::::DDDDD:::::DA:::::A             A:::::A   K:::::::K   K::::::K\n");
        printf("\tS::::::SSSSSS:::::SD:::::::::::::::DDA:::::A               A:::::A  K:::::::K    K:::::K\n");
        printf("\tS:::::::::::::::SS D::::::::::::DDD A:::::A                 A:::::A K:::::::K    K:::::K\n");
        printf("\t SSSSSSSSSSSSSSS   DDDDDDDDDDDDD   AAAAAAA                   AAAAAAAKKKKKKKKK    KKKKKKK\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("--------------------------------------------------- MENU -------------------------------------------------");
        printf("\n1 - Adicionar registro\t\t4 - Apagar registro\t\t\t7 - Pesquisar históricos\n");
        printf("2 - Listar registros\t\t5 - Contar registros de hoje\t\t8 - Ler informação da placa\n");
        printf("3 - Editar registro\t\t6 - Contar registros em uma data\t9 - Encerrar\n");
        printf("----------------------------------------------------------------------------------------------------------\n");
        printf("\a\t\a\t\aEscolha uma opção: \a");
        scanf("%d", &opcao);
        getchar();
        limparTela();

        switch (opcao) {
            case 1:
                adicionarRegistro();
                break;
            case 2:
                listarRegistros();
                break;
            case 3:
                editarRegistro();
                break;
            case 4:
                apagarRegistro();
                break;
            case 5:
                contarRegistrosHoje();
                break;
            case 6:
                contarRegistrosData();
                break;
            case 7:
                pesquisarHistoricos();
                break;
            case 8:
                lerInformacaoPlaca();
                break;
            case 9:
                exit(0);
            default:
                printf("\t\aOpção inválida!\a\n");
                Sleep(1300);
                break;
        }
    }
    return 0;
}
