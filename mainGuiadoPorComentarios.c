#include <stdio.h>      // Inclui a biblioteca padrão de entrada e saída.
#include <stdlib.h>     // Inclui a biblioteca padrão de funções gerais.
#include <locale.h>     // Inclui a biblioteca para lidar com localização (idioma).
#include <windows.h>    // Inclui a biblioteca para funções específicas do Windows.
#include <string.h>     // Inclui a biblioteca para manipulação de strings.
#include <time.h>       // Inclui a biblioteca para lidar com funções relacionadas ao tempo.
#include <dirent.h>     // Inclui a biblioteca para lidar com diretórios.
#include <sys/stat.h>   // Inclui a biblioteca para manipular informações sobre arquivos.

#define MAX_STRING_SIZE 200 // Define uma constante MAX_STRING_SIZE com valor 200.

// Definição da estrutura para armazenar um par de login e senha.
struct Acesso {
    char login[50]; // Campo para armazenar o login.
    char senha[50]; // Campo para armazenar a senha.
};

// Definição da estrutura para armazenar os dados do veículo.
struct Veiculo {
    char data[MAX_STRING_SIZE]; // Campo para armazenar a data.
    char hora[MAX_STRING_SIZE]; // Campo para armazenar a hora.
    char nome[MAX_STRING_SIZE]; // Campo para armazenar o nome.
    char placa[MAX_STRING_SIZE]; // Campo para armazenar a placa.
    char marca[MAX_STRING_SIZE]; // Campo para armazenar a marca.
    char modelo[MAX_STRING_SIZE]; // Campo para armazenar o modelo.
    char cor[MAX_STRING_SIZE]; // Campo para armazenar a cor.
    char observacao[MAX_STRING_SIZE]; // Campo para armazenar observações.
    char municipio[MAX_STRING_SIZE]; // Campo para armazenar o município.
    char cnh[MAX_STRING_SIZE]; // Campo para armazenar a CNH.
    char uf[MAX_STRING_SIZE]; // Campo para armazenar a UF.
    char local[MAX_STRING_SIZE]; // Campo para armazenar o local.
    char numero_local[MAX_STRING_SIZE]; // Campo para armazenar o número do local.
    char bairro[MAX_STRING_SIZE]; // Campo para armazenar o bairro.
};

// Função para fazer comparação de strings (case-insensitive).
char* strcasestr_custom(const char* haystack, const char* needle) {
    while (*haystack) { // Loop enquanto o caractere atual em haystack não for nulo (o final da string)
        const char* h = haystack; // Crie um ponteiro constante 'h' para rastrear o início da haystack atual
        const char* n = needle;   // Crie um ponteiro constante 'n' para rastrear o início da needle atual

        while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n))) {
            // Loop enquanto 'h' e 'n' não forem nulos e os caracteres forem iguais (sem diferenciação entre maiúsculas e minúsculas)
            h++; // Avance o ponteiro 'h' na haystack
            n++; // Avance o ponteiro 'n' na needle
        }

        if (!*n) {
            // Se 'n' se tornar nulo, isso significa que a needle foi totalmente encontrada na haystack
            return (char*)haystack; // Retorne um ponteiro para o início da ocorrência na haystack
        }

        haystack++; // Avance o ponteiro da haystack para continuar a busca
    }

    return NULL; // Se não encontrarmos uma correspondência, retorne NULL
}

// Função para limpar a tela do console no ambiente Windows
void limparTela() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Obtém o identificador do console
    COORD coordScreen = { 0, 0 }; // Define as coordenadas para o canto superior esquerdo da tela
    DWORD cCharsWritten; // Variável para o número de caracteres escritos
    CONSOLE_SCREEN_BUFFER_INFO csbi; // Estrutura para informações sobre o buffer de tela
    DWORD dwConSize; // Variável para o tamanho do buffer de tela

    // Obtém informações sobre o buffer de tela
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y; // Calcula o tamanho do buffer

    // Preenche o buffer de tela com espaços em branco
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
    
    // Move o cursor para o canto superior esquerdo
    SetConsoleCursorPosition(hConsole, coordScreen);
}

// Função para autenticar o usuário
int autenticarUsuario() {
    char login[4] = "ssp"; // Define a senha de acesso.
    char ssp[4]; // Variável para armazenar a entrada do usuário.

    // Define a cor do texto do console como preto (0).
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);

    // Define o título da janela do console como "Digite ssp na tela".
    SetConsoleTitle("Digite ssp na tela");

    scanf("%s", ssp); // Lê a entrada do usuário.

    // Compara a entrada do usuário com a senha.
    if (strcmp(login, ssp) == 0) { // strcmp() é uma função da biblioteca string.h que compara 2 strings. Se for igual a 0 é porque as duas são iguais.
        limparTela(); // Limpa a tela do console.

        // Define o título da janela do console como "SDAK - Sistema de Cadastro de Veículos".
        SetConsoleTitle("SDAK - Sistema de Cadastro de Veículos");

        // Define a cor do texto do console como verde (10).
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

        printf("Acesso autorizado!\n"); // Mensagem de acesso autorizado.

        // Redefine a cor do texto do console para a cor padrão (7).
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        Sleep(1500); // Pausa por 1.5 segundos.
        limparTela(); // Limpa a tela do console.

        int acessoAutorizado; // Variável para verificar o acesso autorizado
        acessoAutorizado = acessarSistemas(); // Chama a função para acessar sistemas.

        // Verifica se o acesso do usuário não foi autorizado.
        if (!acessoAutorizado) { 
            // Exibe uma mensagem informando que é necessário ter acesso.
        	printf("É necessário possuir um sistema de acesso para utilizar o programa.\n");
            getch(); // Aguarda o usuário pressionar qualquer tecla
		    exit(0); // Retorna 0 para indicar que o programa está saindo.
        }

        return 1; // Retorna 1 para indicar acesso autorizado.
    } else {
        // Define o título da janela do console como "ERRO".
        SetConsoleTitle("ERRO");
        // Define a cor do texto do console como vermelho (76).
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 76);
        printf("ACESSO NEGADO!\nErro\n"); // Mensagem de acesso negado.
        // Redefine a cor do texto do console para a cor padrão (0).
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        getch(); // Aguarda o usuário pressionar qualquer tecla
        exit(EXIT_FAILURE); // Encerra o programa com status de falha.
    }
}

// Função para cadastrar novo acesso de sistemas
void cadastrarAcesso() {
    struct Acesso novoAcesso; // Declaração de uma estrutura 'Acesso' para armazenar os dados do novo acesso.
    char resposta; // Declaração de uma variável para armazenar a resposta do usuário.
    int i = 0; // Índice para rastrear a posição atual na senha.
    FILE *arquivo; // Declaração de um ponteiro de arquivo.

    printf("Digite o novo login: "); // Exibe uma mensagem para o usuário solicitar o login.
    scanf("%s", novoAcesso.login); // Lê o login digitado pelo usuário.
    printf("Digite a nova senha: "); // Exibe uma mensagem para o usuário solicitar a senha.
    //scanf("%s", novoAcesso.senha); // Lê a senha digitada pelo usuário.

    // Ler a senha com máscara de "*"
    while (1) {
        char c = getch(); // Lê um caractere sem exibi-lo na tela.

        if (c == 13) { // Se o usuário pressionou Enter (13), encerra a leitura da senha.
            novoAcesso.senha[i] = '\0'; // Adiciona o terminador nulo para marcar o fim da senha.
            break;
        } else if (c == 8 && i > 0) { // Se o usuário pressionou Backspace (8) e a senha não está vazia.
            printf("\b \b"); // Apaga o último caractere digitado.
            i--; // Move o índice para a posição anterior na senha.
        } else if (i < 20 - 1) { // Verifica se o comprimento da senha é menor que o máximo permitido.
            novoAcesso.senha[i] = c; // Armazena o caractere na senha.
            printf("*"); // Exibe um '*' na tela para mascarar a senha.
            i++; // Move o índice para a próxima posição na senha.
        }
    }

    arquivo = fopen("acesso.txt", "a"); // Abre o arquivo "acesso.txt" em modo de apêndice.

    if (arquivo == NULL) { // Verifica se houve erro na abertura do arquivo.
        Sleep(1500); // Pausa por 1.5 segundos
        perror("\nErro ao abrir o arquivo de acesso!\n"); // Exibe uma mensagem de erro padrão.
        return; // Retorna da função.
    }

    fprintf(arquivo, "%s %s\n", novoAcesso.login, novoAcesso.senha); // Escreve o login e a senha no arquivo.
    fclose(arquivo); // Fecha o arquivo.

    printf("\n\nNovo acesso cadastrado com sucesso!\n"); // Exibe uma mensagem de sucesso.
    Sleep(1500); // Pausa por 1.5 segundos
    limparTela();
    acessarSistemas(); // Chama a função acessarSistemas.
}

// Função para verificar o acesso e contar tentativas
int acessarSistemas() {
    struct Acesso acesso; // Declaração de uma estrutura 'Acesso' para armazenar os dados de acesso.
    char inputLogin[50]; // Declaração de uma variável para armazenar o login inserido pelo usuário.
    char inputSenha[50]; // Declaração de uma variável para armazenar a senha inserida pelo usuário.
    int acessoAutorizado = 0; // Declaração de uma variável para verificar se o acesso foi autorizado.
    int tentativas = 0; // Declaração de uma variável para contar o número de tentativas.
    FILE *arquivo; // Declaração de um ponteiro de arquivo.

    arquivo = fopen("acesso.txt", "r"); // Abre o arquivo "acesso.txt" em modo de leitura.

    if (arquivo == NULL) { // Verifica se o arquivo não foi encontrado.
        char resposta; // Declara uma variável chamada 'resposta' para armazenar a resposta do usuário.
        int c; // Declara uma variável chamada 'c' para armazenar caracteres lidos.
        do {
            printf("Arquivo de acesso não encontrado. Deseja criar um novo arquivo de acesso? (S/N): "); // Exibe uma mensagem para o usuário.
            c = getchar();
        } while (c != EOF && c != '\n'); // Executa um loop para limpar o buffer de entrada até encontrar um fim de linha ou o final do arquivo.

        resposta = getchar(); // Lê a resposta do usuário.

        if (resposta == 'S' || resposta == 's') { // Verifica se o usuário deseja criar um novo arquivo.
            arquivo = fopen("acesso.txt", "w"); // Abre o arquivo "acesso.txt" em modo de escrita.

            if (arquivo == NULL) { // Verifica se houve erro na abertura do arquivo.
                perror("Erro ao criar o arquivo de acesso!\n"); // Exibe uma mensagem de erro padrão.
                Sleep(1500); // Pausa por 1.5 segundos
                return 0; // Retorna 0 para indicar falha.
            } else {
                printf("Arquivo de acesso criado com sucesso.\n"); // Exibe uma mensagem de sucesso.
                Sleep(1500); // Pausa por 1.5 segundos
                limparTela(); // Limpar a tela
                cadastrarAcesso(); // Chama a função cadastrarAcesso para adicionar um novo acesso.
                fclose(arquivo); // Fecha o arquivo.
                return 1; // Retorna 1 para indicar sucesso.
            }
        } else {
            fclose(arquivo); // Fecha o arquivo.
            return 0; // Retorna 0 para indicar que o usuário optou por não criar um novo arquivo.
        }
    }

    while (1) { // Loop infinito para solicitar login e senha até o acesso ser autorizado ou atingir o limite de tentativas.
        printf("Digite o login (ou 'q' para sair): "); // Exibe uma mensagem para o usuário solicitar o login.
        scanf("%s", inputLogin); // Lê o login inserido pelo usuário.

        if (strcmp(inputLogin, "Q") == 0 || strcmp(inputLogin, "q") == 0) { // Verifica se o usuário deseja sair.
            printf("Encerrando o programa...\n"); // Exibe uma mensagem de saída.
            fclose(arquivo); // Fecha o arquivo.
            Sleep(1500); // Pausa por 1.5 segundos
            exit(0); // Retorna 0 para indicar que o programa está saindo.
        }

        printf("Digite a senha: "); // Exibe uma mensagem para o usuário solicitar a senha.
        //scanf("%s", inputSenha); // Lê a senha inserida pelo usuário.

        int i = 0; // Índice para rastrear a posição atual na senha.

        while (1) {
            char c = getch(); // Lê um caractere sem exibi-lo na tela.

            if (c == 13) { // Se o usuário pressionou Enter (13), encerra a leitura da senha.
                inputSenha[i] = '\0'; // Adiciona o terminador nulo para marcar o fim da senha.
                break;
            } else if (c == 8 && i > 0) { // Se o usuário pressionou Backspace (8) e a senha não está vazia.
                printf("\b \b"); // Apaga o último caractere digitado.
                i--; // Move o índice para a posição anterior na senha.
            } else if (i < 20) { // Verifica se o comprimento da senha é menor que o máximo permitido.
                inputSenha[i] = c; // Armazena o caractere na senha.
                printf("*"); // Exibe um '*' na tela para mascarar a senha.
                i++; // Move o índice para a próxima posição na senha.
            }
        }

        fseek(arquivo, 0, SEEK_SET); // Volta para o início do arquivo.

        while (fscanf(arquivo, "%s %s", acesso.login, acesso.senha) == 2) { // Loop para ler pares de login e senha do arquivo.
            if (strcmp(inputLogin, acesso.login) == 0 && strcmp(inputSenha, acesso.senha) == 0) { // Verifica se o login e a senha coincidem.
                acessoAutorizado = 1; // Define acessoAutorizado como 1 para indicar que o acesso foi autorizado.
                break; // Sai do loop.
            }
        }

        if (acessoAutorizado) { // Verifica se o acesso foi autorizado.
        	limparTela(); // Limpa a tela
        	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Para redefinir a cor normal, defina-a como color
            printf("Acesso autorizado! Bem-vindo, %s.\n", inputLogin); // Exibe uma mensagem de sucesso.
            Sleep(2000); // Pausa por 2 segundos
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Para redefinir a cor normal, defina-a como color
            break; // Sai do loop.
        } else {
            printf("Acesso Negado! Verifique o login e a senha.\n"); // Exibe uma mensagem de acesso negado.
            tentativas++; // Incrementa o número de tentativas.

            if (tentativas >= 3) { // Verifica se o limite de tentativas foi atingido.
                printf("Limite de tentativas excedido. Saindo do programa.\n"); // Exibe uma mensagem de limite excedido.
                fclose(arquivo); // Fecha o arquivo.
                Sleep(1500); // Aguarde por 1.5 segundos
                exit(1); // Sai do programa com código de erro.
            }
        }
    }

    fclose(arquivo); // Fecha o arquivo.
    return acessoAutorizado; // Retorna 1 para indicar que o acesso foi autorizado ou 0 caso contrário.
}

// Função para adicionar um novo registro
void adicionarRegistro() {
    struct Veiculo veiculo; // Declaração de uma estrutura 'Veiculo' para armazenar os dados do veículo.
    char placaArquivo[30]; // Declaração de uma variável para armazenar o nome do arquivo com base na placa.

    printf("Digite a data (no formato AAAA-MM-DD): "); // Exibe uma mensagem para o usuário solicitar a data.
    fgets(veiculo.data, sizeof(veiculo.data), stdin); // Lê a data digitada pelo usuário.
    veiculo.data[strcspn(veiculo.data, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite a hora (no formato HH:MM): "); // Exibe uma mensagem para o usuário solicitar a hora.
    fgets(veiculo.hora, sizeof(veiculo.hora), stdin); // Lê a hora digitada pelo usuário.
    veiculo.hora[strcspn(veiculo.hora, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite o nome: "); // Exibe uma mensagem para o usuário solicitar o nome.
    fgets(veiculo.nome, sizeof(veiculo.nome), stdin); // Lê o nome digitado pelo usuário.
    veiculo.nome[strcspn(veiculo.nome, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite a placa: "); // Exibe uma mensagem para o usuário solicitar a placa.
    fgets(veiculo.placa, sizeof(veiculo.placa), stdin); // Lê a placa digitada pelo usuário.
    veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite a marca: "); // Exibe uma mensagem para o usuário solicitar a marca.
    fgets(veiculo.marca, sizeof(veiculo.marca), stdin); // Lê a marca digitada pelo usuário.
    veiculo.marca[strcspn(veiculo.marca, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite o modelo: "); // Exibe uma mensagem para o usuário solicitar o modelo.
    fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin); // Lê o modelo digitado pelo usuário.
    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite a cor: "); // Exibe uma mensagem para o usuário solicitar a cor.
    fgets(veiculo.cor, sizeof(veiculo.cor), stdin); // Lê a cor digitada pelo usuário.
    veiculo.cor[strcspn(veiculo.cor, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite a observação: "); // Exibe uma mensagem para o usuário solicitar a observação.
    fgets(veiculo.observacao, sizeof(veiculo.observacao), stdin); // Lê a observação digitada pelo usuário.
    veiculo.observacao[strcspn(veiculo.observacao, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite o município: "); // Exibe uma mensagem para o usuário solicitar o município.
    fgets(veiculo.municipio, sizeof(veiculo.municipio), stdin); // Lê o município digitado pelo usuário.
    veiculo.municipio[strcspn(veiculo.municipio, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite o número da CNH: "); // Exibe uma mensagem para o usuário solicitar o número da CNH.
    fgets(veiculo.cnh, sizeof(veiculo.cnh), stdin); // Lê o número da CNH digitado pelo usuário.
    veiculo.cnh[strcspn(veiculo.cnh, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite a UF: "); // Exibe uma mensagem para o usuário solicitar a UF.
    fgets(veiculo.uf, sizeof(veiculo.uf), stdin); // Lê a UF digitada pelo usuário.
    veiculo.uf[strcspn(veiculo.uf, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite o local: "); // Exibe uma mensagem para o usuário solicitar o local.
    fgets(veiculo.local, sizeof(veiculo.local), stdin); // Lê o local digitado pelo usuário.
    veiculo.local[strcspn(veiculo.local, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite o número do local: "); // Exibe uma mensagem para o usuário solicitar o número do local.
    fgets(veiculo.numero_local, sizeof(veiculo.numero_local), stdin); // Lê o número do local digitado pelo usuário.
    veiculo.numero_local[strcspn(veiculo.numero_local, "\n")] = '\0'; // Remove o caractere de nova linha.

    printf("Digite o bairro: "); // Exibe uma mensagem para o usuário solicitar o bairro.
    fgets(veiculo.bairro, sizeof(veiculo.bairro), stdin); // Lê o bairro digitado pelo usuário.
    veiculo.bairro[strcspn(veiculo.bairro, "\n")] = '\0'; // Remove o caractere de nova linha.

    FILE *arquivo; // Declaração de um ponteiro de arquivo.

    snprintf(placaArquivo, sizeof(placaArquivo), "%s.txt", veiculo.placa); // Gera o nome do arquivo com base na placa.

    arquivo = fopen(placaArquivo, "a"); // Abre o arquivo com o nome gerado em modo de apêndice.

    if (arquivo == NULL) { // Verifica se houve erro na abertura do arquivo.
        perror("O arquivo não pode ser aberto.\n"); // Exibe uma mensagem de erro.
        Sleep(1300);
        return; // Retorna da função.
    }

    fprintf(arquivo, "Data e Hora: %s %s\n", veiculo.data, veiculo.hora); // Escreve a data e a hora no arquivo.
    fprintf(arquivo, "Nome: %s\n", veiculo.nome); // Escreve o nome no arquivo.
    fprintf(arquivo, "Placa: %s\n", veiculo.placa); // Escreve a placa no arquivo.
    fprintf(arquivo, "Marca: %s\n", veiculo.marca); // Escreve a marca no arquivo.
    fprintf(arquivo, "Modelo: %s\n", veiculo.modelo); // Escreve o modelo no arquivo.
    fprintf(arquivo, "Cor: %s\n", veiculo.cor); // Escreve a cor no arquivo.
    fprintf(arquivo, "Observação: %s\n", veiculo.observacao); // Escreve a observação no arquivo.
    fprintf(arquivo, "Município: %s\n", veiculo.municipio); // Escreve o município no arquivo.
    fprintf(arquivo, "CNH: %s\n", veiculo.cnh); // Escreve a CNH no arquivo.
    fprintf(arquivo, "UF: %s\n", veiculo.uf); // Escreve a UF no arquivo.
    fprintf(arquivo, "Local: %s\n", veiculo.local); // Escreve o local no arquivo.
    fprintf(arquivo, "Número do Local: %s\n", veiculo.numero_local); // Escreve o número do local no arquivo.
    fprintf(arquivo, "Bairro: %s", veiculo.bairro); // Escreve o bairro no arquivo.

    fflush(arquivo); // Força a gravação imediata no arquivo
    printf("\nRegistro adicionado com sucesso no arquivo %s.\n", placaArquivo); // Exibe uma mensagem de sucesso.
    Sleep(2000); // Pausa por 2 segundos
}

// Função para listar registros em um arquivo específico
void listarRegistrosArquivo(const char *nomeArquivo) {
    struct Veiculo veiculo; // Declaração de uma estrutura 'Veiculo' para armazenar os dados do veículo.
    char buffer[2000]; // Buffer para ler uma linha inteira do arquivo (aumentado para 2000 caracteres)

    FILE *arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo especificado em modo de leitura.

    if (arquivo == NULL) { // Verifica se houve erro na abertura do arquivo.
        perror("O arquivo não existe ou não pode ser aberto.\n"); // Exibe uma mensagem de erro padrão.
        Sleep(1500); // Pausa por 1.5 segundos
        return; // Retorna da função.
    }

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) { // Loop para ler cada linha do arquivo.
        if (strstr(buffer, "Data e Hora: ") == buffer) { // Verifica se a linha começa com "Data e Hora: ".
            if (sscanf(buffer, "Data e Hora: %s %s", veiculo.data, veiculo.hora) != 2) { // Lê a data e a hora.
                continue; // Pula para a próxima linha se não for possível ler a data e a hora.
            }

            // Lê os demais campos do veículo a partir do arquivo.
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
                continue; // Pula para a próxima linha se não for possível ler algum campo.
            }

            // Remove o caractere de nova linha de cada campo.
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

            // Exibe os dados do veículo.
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
            printf("\n_____________________\n\n"); // Linha de separação entre registros.
        }
    }

    fclose(arquivo); // Fecha o arquivo.
}

// Função para listar registros em todos os arquivos com extensão .txt
void listarRegistros() {
    const char *diretorio = "."; // Define o diretório atual como local de busca dos arquivos
    DIR *dp; // Declara uma variável para representar o diretório
    struct dirent *entry; // Declara uma variável para representar uma entrada de diretório

    dp = opendir(diretorio); // Abre o diretório especificado

    if (dp == NULL) { // Verifica se houve erro na abertura do diretório
        perror("opendir"); // Exibe uma mensagem de erro padrão
        Sleep(1500); // Pausa por 1.5 segundos
        return; // Retorna da função
    }

    while ((entry = readdir(dp))) { // Loop para percorrer todas as entradas de diretório no diretório atual
        // Verifique se o nome do arquivo termina com ".txt" e não é o arquivo "acesso.txt".
        if (strstr(entry->d_name, ".txt") != NULL && strcmp(entry->d_name, "acesso.txt") != 0) { // Verifica se o nome do arquivo possui a extensão .txt
            printf("Listando registros para arquivo %s:\n\n", entry->d_name); // Exibe o nome do arquivo
            listarRegistrosArquivo(entry->d_name); // Chama a função para listar registros no arquivo
            printf("\n"); // Imprime uma linha em branco para separar os resultados
        }
    }

    closedir(dp); // Fecha o diretório após listar os registros
    getch(); // Aguarda o usuário pressionar qualquer tecla
}

// Função para buscar e editar um registro
void editarRegistro() {
    struct Veiculo veiculo; // Declaração de uma estrutura 'Veiculo' para armazenar os dados do veículo.
    char placaBusca[20]; // Declaração de uma variável para armazenar a placa de busca.
    char buffer[2000]; // Declaração de um buffer para ler linhas do arquivo.
    char nomeArquivo[30]; // Declaração de uma variável para armazenar o nome do arquivo.

    char novoNomeArquivo[50]; // Declaração de uma variável para armazenar o novo nome do arquivo após a edição.
    int encontrado = 0; // Variável para indicar se o registro foi encontrado.

    printf("Digite a placa do veículo que deseja editar (ou digite 'q' para sair): "); // Solicitação para digitar a placa de busca.
    fgets(placaBusca, sizeof(placaBusca), stdin); // Lê a placa de busca digitada pelo usuário.
    placaBusca[strcspn(placaBusca, "\n")] = '\0'; // Remove o caractere de nova linha.

    if (placaBusca[0] == 'q') { // Verifica se o usuário digitou 'q' para sair.
        return; // Retorna da função.
    }

    if (placaBusca[0] == '\0' || placaBusca[0] == ' ') { // Verifica se o termo de busca está vazio.
        printf("O termo de busca não pode ser vazio.\n"); // Exibe uma mensagem de erro.
        Sleep(1500); // Pausa por 1.5 segundos
        return; // Retorna da função.
    }

    // Adicione a extensão .txt ao nome do arquivo (não utilizado).
    //strcat(placaBusca, ".txt");
    
    // Construí o nome do arquivo com base na placa fornecida pelo usuário.
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", placaBusca); 

    FILE *arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo especificado em modo de leitura.

    FILE *tempArquivo = fopen("temp.txt", "w"); // Abre um arquivo temporário em modo de escrita.
    if (tempArquivo == NULL) { // Verifica se houve erro na abertura do arquivo temporário.
        perror("Erro ao criar arquivo temporário.\n"); // Exibe uma mensagem de erro padrão.
        Sleep(1500); // Pausa por 1.5 segundos
        return; // Retorna da função.
    }

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) { // Loop para ler cada linha do arquivo.
        if (strstr(buffer, "Data e Hora: ") == buffer) { // Verifica se a linha começa com "Data e Hora: ".
            if (sscanf(buffer, "Data e Hora: %s %s", veiculo.data, veiculo.hora) != 2) { // Lê a data e a hora.
                continue; // Pula para a próxima linha se não for possível ler a data e a hora.
            }

            // Lê os demais campos do veículo a partir do arquivo.
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
                continue; // Pula para a próxima linha se não for possível ler algum campo.
            }

            if (strcmp(veiculo.placa, placaBusca) != 0) { // Verifica se a placa do veículo corresponde à busca.
                encontrado = 1; // Define a variável encontrado como 1 para indicar que o registro foi encontrado.

                // Exibe os dados do veículo encontrado.
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
                printf("Deseja editar este registro? (S/N): "); // Solicitação para confirmar a edição.
                fgets(resposta, sizeof(resposta), stdin); // Lê a resposta do usuário.

                if (toupper(resposta[0]) == 'S') { // Verifica se a resposta começa com 'S' (confirmação da edição).
                    getchar(); // Lê um caractere em branco.

                    // Solicita ao usuário que informe os novos dados.
                    printf("\nInforme novos dados\n\nDigite a data (no formato AAAA-MM-DD): ");
                    fgets(veiculo.data, sizeof(veiculo.data), stdin);
                    veiculo.data[strcspn(veiculo.data, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite a hora (no formato HH:MM): ");
                    fgets(veiculo.hora, sizeof(veiculo.hora), stdin);
                    veiculo.hora[strcspn(veiculo.hora, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite o nome: ");
                    fgets(veiculo.nome, sizeof(veiculo.nome), stdin);
                    veiculo.nome[strcspn(veiculo.nome, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite a placa: ");
                    fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
                    veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite a marca: ");
                    fgets(veiculo.marca, sizeof(veiculo.marca), stdin);
                    veiculo.marca[strcspn(veiculo.marca, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite o modelo: ");
                    fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
                    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite a cor: ");
                    fgets(veiculo.cor, sizeof(veiculo.cor), stdin);
                    veiculo.cor[strcspn(veiculo.cor, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite a observação: ");
                    fgets(veiculo.observacao, sizeof(veiculo.observacao), stdin);
                    veiculo.observacao[strcspn(veiculo.observacao, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite o município: ");
                    fgets(veiculo.municipio, sizeof(veiculo.municipio), stdin);
                    veiculo.municipio[strcspn(veiculo.municipio, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite o número da CNH: ");
                    fgets(veiculo.cnh, sizeof(veiculo.cnh), stdin);
                    veiculo.cnh[strcspn(veiculo.cnh, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite a UF: ");
                    fgets(veiculo.uf, sizeof(veiculo.uf), stdin);
                    veiculo.uf[strcspn(veiculo.uf, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite o local: ");
                    fgets(veiculo.local, sizeof(veiculo.local), stdin);
                    veiculo.local[strcspn(veiculo.local, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite o número do local: ");
                    fgets(veiculo.numero_local, sizeof(veiculo.numero_local), stdin);
                    veiculo.numero_local[strcspn(veiculo.numero_local, "\n")] = '\0'; // Remove o caractere de nova linha.

                    printf("Digite o bairro: ");
                    fgets(veiculo.bairro, sizeof(veiculo.bairro), stdin);
                    veiculo.bairro[strcspn(veiculo.bairro, "\n")] = '\0'; // Remove o caractere de nova linha.

                    // Escreve os novos dados no arquivo temporário.
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
                    fprintf(tempArquivo, "Número do Local: %s\n", veiculo.numero_local);
                    fprintf(tempArquivo, "Bairro: %s\n", veiculo.bairro);

                    printf("\nRegistro editado com sucesso.\n");

                    sprintf(novoNomeArquivo, "%s.txt", veiculo.placa); // Gera o novo nome do arquivo com base na placa atualizada.

                    fflush(tempArquivo); // Limpa o buffer e escreve os dados no arquivo.
                    Sleep(1500); // Pausa por 1.5 segundos

                } else { // Caso o usuário não queira editar o registro.
                    encontrado = 0; // Define a variável encontrado como 0 para indicar que o registro não deve ser excluído.

                    // Escreve os dados originais do veículo no arquivo temporário.
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
            continue; // Continua para a próxima linha se a linha não começar com "Data e Hora: ".
        }
    }

    fclose(tempArquivo); // Fecha o arquivo temporário.
    fclose(arquivo); // Fecha o arquivo original.

    if (encontrado) { // Verifica se o registro foi encontrado.
        remove(nomeArquivo); // Remove o arquivo original.
        rename("temp.txt", novoNomeArquivo); // Renomeia o arquivo temporário para o novo nome.
    } else {
        remove("temp.txt"); // Remove o arquivo temporário se o registro não foi encontrado.
        printf("Registro não encontrado.\n"); // Exibe uma mensagem se o registro não for encontrado.
        Sleep(1500); // Pausa por 1.5 segundos
    }
}

// Função para apagar um registro
void apagarRegistro() {
    struct Veiculo veiculo; // Declaração de uma estrutura 'Veiculo' para armazenar os dados do veículo.
    char placaBusca[20]; // Declaração de uma variável para armazenar a placa de busca.
    char nomeArquivo[30]; // Declaração de uma variável para armazenar o nome do arquivo.
    int encontrado = 0; // Variável para indicar se o registro foi encontrado.

    printf("Digite a placa do veículo que deseja apagar (ou digite 'q' para sair): "); // Solicitação para digitar a placa de busca.
    fgets(placaBusca, sizeof(placaBusca), stdin); // Lê a placa de busca digitada pelo usuário.
    placaBusca[strcspn(placaBusca, "\n")] = '\0'; // Remove o caractere de nova linha.

    if (placaBusca[0] == 'q') { // Verifica se o usuário digitou 'q' para sair.
        return; // Retorna da função.
    }

    if (placaBusca[0] == '\0' || placaBusca[0] == ' ') { // Verifica se o termo de busca está vazio.
        printf("O termo de busca não pode ser vazio.\n"); // Exibe uma mensagem de erro.
        Sleep(1500); // Pausa por 1.5 segundos
        return; // Retorna da função.
    }

    // Abre o nome do arquivo com base na placa fornecida pelo usuário.
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", placaBusca);

    FILE *arquivo = fopen(nomeArquivo, "r+"); // Abre o arquivo especificado em modo de leitura e escrita.
    FILE *tempFile = fopen("temp.txt", "w"); // Abre um arquivo temporário em modo de escrita.

    while (fgets(veiculo.data, sizeof(veiculo.data), arquivo) != NULL) { // Loop para ler cada linha do arquivo.
        /*if (strstr(veiculo.data, "Data e Hora: ") != veiculo.data) {
            continue; // Ignorar linhas que não começam com "Data e Hora: "
        }*/

        // Ler as informações do veículo
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

        // Verificar se a placa corresponde à busca
        if (strcmp(veiculo.placa, placaBusca) != 0) { // Compara a placa fornecida com a placa do veículo atual
            encontrado = 1; // Define a variável encontrado como 1 para indicar que o registro foi encontrado
            
            // Exibe os dados do veículo encontrado.
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
            printf("Deseja confirmar a exclusão deste registro? (S/N): "); // Solicitação para confirmar a exclusão.
            fgets(resposta, sizeof(resposta), stdin);

            if (toupper(resposta[0]) == 'S') { // Verifica se a resposta começa com 'S' (confirmação da exclusão).
                remove(nomeArquivo); // Remove o arquivo original.
                printf("\nO registro foi excluído com sucesso!"); // Exibe uma mensagem de exclusão concluída.
                Sleep(1500); // Pausa por 1.5 segundos
                continue; // Continua para o próximo registro.
            }
        }
    }
    
    fclose(arquivo); // Fecha o arquivo original.
    fclose(tempFile); // Fecha o arquivo temporário.

    if (!encontrado) { // Verifica se o registro não foi encontrado.
        printf("Registro não encontrado.\n"); // Exibe uma mensagem.
        Sleep(1500); // Pausa por 1.5 segundos
    }

    remove("temp.txt"); // Remove o arquivo temporário.
}

// Função para contar registros de hoje
void contarRegistrosHoje() {
    struct tm *today; // Declaração de uma estrutura para armazenar a data atual.
    char nomeArquivo[30]; // Declaração de uma variável para armazenar o nome do arquivo.
    int contador = 0; // Variável para contar o número de arquivos encontrados criados hoje.
    time_t now; // Declaração de uma variável para armazenar a hora atual.

    time(&now); // Obtém a hora atual.
    today = localtime(&now); // Obtém a data e hora local com base na hora atual.

    char dataAtual[11]; // Declaração de uma variável para armazenar a data atual formatada.
    strftime(dataAtual, sizeof(dataAtual), "%Y-%m-%d", today); // Formata a data atual.

    DIR *dir; // Declaração de um ponteiro para um diretório.
    struct dirent *ent; // Declaração de uma estrutura para armazenar informações sobre um arquivo/diretório.

    if ((dir = opendir(".")) != NULL) { // Abre o diretório atual.
        while ((ent = readdir(dir)) != NULL) { // Loop para iterar através dos arquivos/diretórios no diretório.
            if (strstr(ent->d_name, ".txt") != NULL && strcmp(ent->d_name, "acesso.txt") != 0) { // Verifica se o arquivo possui extensão .txt e não é "acesso.txt".
                struct stat st; // Declaração de uma estrutura para armazenar informações sobre um arquivo.
                stat(ent->d_name, &st); // Obtém informações sobre o arquivo.
                struct tm *fileTime = localtime(&st.st_mtime); // Obtém a data e hora de modificação do arquivo.

                char fileDate[11]; // Declaração de uma variável para armazenar a data de modificação do arquivo formatada.
                strftime(fileDate, sizeof(fileDate), "%Y-%m-%d", fileTime); // Formata a data de modificação do arquivo.

                if (strcmp(fileDate, dataAtual) == 0) { // Verifica se a data de modificação do arquivo é igual à data atual.
                    //printf("\nxxxxxxxxxxxxxxxxxxx\n");
                    printf("Nome do arquivo encontrado: %s\n\n", ent->d_name); // Exibe o nome do arquivo encontrado.
                    printf("A data atual: %s\n", dataAtual); // Exibe a data atual formatada.
                    printf("A data de modificação do arquivo: %s\n", fileDate); // Exibe a data de modificação do arquivo formatada.
                    printf("\n______________________\n\n");
                    contador++; // Incrementa o contador.
                }
            }
        }
        closedir(dir); // Fecha o diretório.
    }

    printf("\nForam encontrados %d arquivos criados hoje.\n", contador); // Exibe o número de arquivos encontrados.
    getch(); // Aguarda o usuário pressionar qualquer tecla
}

// Função para contar registros em uma data específica do arquivo
void contarRegistrosData() {
    struct tm *today; // Inicializa o ponteiro para a estrutura tm que armazenará a data atual.
    char nomeArquivo[30]; // Inicializa uma string para armazenar o nome do arquivo.
    int contador = 0; // Inicializa um contador para armazenar o número de arquivos encontrados.
    time_t now; // Declaração de uma variável para armazenar a hora atual.

    time(&now); // Obtém a hora atual do sistema.
    today = localtime(&now); // Obtém a data e hora local com base na hora atual.

    char dataBusca[20]; // Declaração de uma variável para armazenar a data de busca.
    printf("Digite a data (no formato AAAA-MM-DD) (ou digite 'q' para sair): "); // Solicita ao usuário que digite a data.
    fgets(dataBusca, sizeof(dataBusca), stdin); // Lê a data fornecida pelo usuário.
    dataBusca[strcspn(dataBusca, "\n")] = '\0'; // Remove o caractere de nova linha do final da data.

    if (dataBusca[0] == 'q') { // Verifica se o usuário digitou 'q' para sair.
        return; // Retorna da função.
    }

    if (dataBusca[0] == '\0' || dataBusca[0] == ' ') { // Verifica se a data fornecida está vazia.
        printf("O termo de busca não pode ser vazio.\n"); // Exibe uma mensagem de erro.
        Sleep(1500); // Pausa por 1.5 segundos
        return; // Retorna da função.
    }

    DIR *dir; // Declaração de um ponteiro para um diretório.
    struct dirent *ent; // Declaração de uma estrutura para armazenar informações sobre um arquivo/diretório.

    if ((dir = opendir(".")) != NULL) { // Abre um diretório para ler todos os arquivos no diretório atual.
        // Percorre todos os arquivos no diretório.
        while ((ent = readdir(dir)) != NULL) {
            // Verifica se o arquivo é um arquivo de texto com extensão ".txt" e não é o arquivo "acesso.txt".
            if (strstr(ent->d_name, ".txt") != NULL && strcmp(ent->d_name, "acesso.txt") != 0) {
                struct stat st; // Declaração de uma estrutura para armazenar informações sobre um arquivo.
                stat(ent->d_name, &st); // Obtém informações sobre o arquivo.
                struct tm *fileTime = localtime(&st.st_mtime); // Obtém a data e hora de modificação do arquivo.

                char fileDate[11]; // Declaração de uma variável para armazenar a data de modificação do arquivo formatada.
                strftime(fileDate, sizeof(fileDate), "%Y-%m-%d", fileTime); // Formata a data de modificação do arquivo.

                // Verifica se a data de modificação do arquivo é igual à data atual.
                if (strcmp(fileDate, dataBusca) == 0) {
                    // Imprime informações sobre o arquivo encontrado.
                	printf("Nome do arquivo encontrado: %s\n\n", ent->d_name); // Exibe o nome do arquivo encontrado.
                    printf("A data digitada: %s\n", dataBusca); // Exibe a data atual formatada.
                    printf("A data de modificação do arquivo: %s\n", fileDate); // Exibe a data de modificação do arquivo formatada.
                    printf("\n______________________\n\n");
                    contador++; // Incrementa o contador.
                }
            }
        }
        closedir(dir); // Fecha o diretório.
    }
    // Imprime o número de arquivos encontrados.
    printf("\nForam encontrados %d arquivos criados na data %s.\n", contador, dataBusca);
    getch(); // Aguarda o usuário pressionar qualquer tecla
}

// Função para pesquisar por placa do veículo
void lerInformacaoPlaca() {
    struct Veiculo veiculo; // Declaração de uma estrutura para armazenar informações do veículo.
    char placaBusca[50]; // Declaração de uma variável para armazenar a placa fornecida pelo usuário.
    char nomeArquivo[30]; // Declaração de uma variável para armazenar o nome do arquivo.
    char buffer[2000]; // Declaração de um buffer para armazenar linhas do arquivo.
    int encontrado = 0; // Variável para indicar se a placa foi encontrada ou não.

    printf("Digite a placa do veículo que deseja pesquisar (ou digite 'q' para sair): "); // Solicita ao usuário que digite a placa.
    fgets(placaBusca, sizeof(placaBusca), stdin); // Lê a placa fornecida pelo usuário.
    placaBusca[strcspn(placaBusca, "\n")] = '\0'; // Remove o caractere de nova linha do final da placa.

    if (placaBusca[0] == 'q') { // Verifica se o usuário digitou 'q' para sair.
        return; // Retorna da função.
    }

    if (placaBusca[0] == '\0' || placaBusca[0] == ' ') { // Verifica se a placa fornecida está vazia.
        printf("O termo de busca não pode ser vazio.\n"); // Exibe uma mensagem de erro.
        Sleep(1500); // Pausa por 1.5 segundos
        return; // Retorna da função.
    }
    
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", placaBusca);

    FILE *arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo para leitura.

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) { // Loop para ler as linhas do arquivo.
        if (strstr(buffer, "Data e Hora: ") == buffer) { // Verifica se a linha começa com "Data e Hora: ".
            if (sscanf(buffer, "Data e Hora: %s %s", veiculo.data, veiculo.hora) != 2) {
                // Se a linha não contém data e hora válidas, pule o registro
                continue;
            }
            
            // Lê os demais campos do veículo a partir do arquivo.
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
        
            // Remova a quebra de linha do final de cada campo
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

	        if (strcmp(veiculo.placa, placaBusca) != 0 ){// Verifica se a placa do veículo corresponde à busca.
	            encontrado = 1; // Define a variável encontrado como 1 para indicar que um registro correspondente foi encontrado
	            
                // Exibe os dados do veículo encontrado.
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

    if (!encontrado) { // Verifica se o registro não foi encontrado.
        printf("Nenhum registro encontrado com a placa \"%s\".\n", placaBusca); // Exibe uma mensagem.
    }
	fclose(arquivo); // Fecha o arquivo.
    getch(); // Aguarda o usuário pressionar qualquer tecla
}

// Função para pesquisar históricos
void pesquisarHistoricos() {
	char termoBusca[100]; // Declaração de uma variável para armazenar o termo de busca.
    char linha[1000]; // Declaração de um buffer para armazenar linhas dos arquivos.
    int encontrado = 0; // Variável para indicar se o termo foi encontrado ou não.
    int linhaAtual = 0; // Variável para acompanhar a linha atual enquanto lê os arquivos.

    while (1) { // Loop infinito para a pesquisa.
        printf("Digite a palavra que deseja pesquisar nos históricos (ou digite 'q' para sair): "); // Solicita ao usuário que digite o termo de busca.
        fgets(termoBusca, sizeof(termoBusca), stdin); // Lê o termo de busca fornecido pelo usuário.
        termoBusca[strcspn(termoBusca, "\n")] = '\0'; // Remove o caractere de nova linha do final do termo.

        if (termoBusca[0] == 'q') { // Verifica se o usuário digitou 'q' para sair.
            break; // Sai do loop.
        }
        
	    if (termoBusca[0] == '\0' || termoBusca[0] == ' ') { // Verifica se o termo de busca está vazio.
	        printf("O termo de busca não pode ser vazio.\n"); // Exibe uma mensagem de erro.
	        Sleep(1500); // Pausa por 1.5 segundos
            break; // Sai do loop.
	    }

        DIR *dir; // Declaração de uma variável de diretório.
        struct dirent *ent; // Declaração de uma variável de entrada de diretório.
        if ((dir = opendir(".")) != NULL) { // Abre o diretório atual.
            while ((ent = readdir(dir)) != NULL) { // Loop para percorrer as entradas no diretório.
                // Verifica se a entrada é um arquivo .txt e não é o arquivo "acesso.txt".
                if (strstr(ent->d_name, ".txt") != NULL && strcmp(ent->d_name, "acesso.txt") != 0) {

                    FILE *arquivo = fopen(ent->d_name, "r"); // Abre o arquivo para leitura.
                    if (arquivo != NULL) { // Verifica se o arquivo foi aberto com sucesso.
                        linhaAtual = 0; // Reinicia o contador de linhas.

                        while (fgets(linha, sizeof(linha), arquivo) != NULL) { // Loop para ler as linhas do arquivo.
                            linhaAtual++; // Incrementa o contador de linhas.

                            if (strcasestr_custom(linha, termoBusca) != NULL) { // Verifica se o termo de busca foi encontrado na linha (ignorando maiúsculas/minúsculas).
                                encontrado = 1; // Define a variável encontrado como 1 para indicar que o termo foi encontrado.
                                printf("Palavra encontrada na linha %d do arquivo %s:\n", linhaAtual, ent->d_name); // Exibe a informação sobre onde o termo foi encontrado.
                                printf("%s\n", linha); // Exibe a linha onde o termo foi encontrado.
                            }
                        }
                        fclose(arquivo); // Fecha o arquivo após a leitura.
                    }
                }
            }
            closedir(dir); // Fecha o diretório após a busca.
        }

        if (!encontrado) { // Verifica se o termo não foi encontrado em nenhum arquivo.
            printf("A palavra '%s' não foi encontrada em nenhum arquivo de histórico.\n", termoBusca); // Exibe uma mensagem informando que o termo não foi encontrado.
        } else { // Se o termo foi encontrado em pelo menos um arquivo.
            lerInformacaoPlaca(); // Chama a função lerInformacaoPlaca para buscar informações adicionais com base na placa encontrada.
            encontrado = 0; // Reinicia a variável encontrado para a próxima pesquisa.
        }
    } // Fim do while
}

// Função executar o menu prinicipal
int main() {
	setlocale(LC_ALL, ""); // Configura o locale para as configurações regionais padrão do sistema

    int opcao; // Variável para armazenar a opção do menu

    autenticarUsuario(); // Chama a função para autenticar o usuário.

    while (1) { // Loop infinito para exibir o menu principal repetidamente
    	time_t tempoAtual; // Variável para armazenar o tempo atual em segundos desde 01/01/1970
		struct tm *tempoInfo; // Estrutura para armazenar informações de tempo local
		char horaString[9]; // Para armazenar a hora (hh:mm:ss)
		char dataString[11]; // Para armazenar a data (dd/mm/yyyy)
		
		time(&tempoAtual); // Obtém o tempo atual do sistema
		tempoInfo = localtime(&tempoAtual); // Obtém informações de tempo local com base no tempo atual
		
		// Formata o tempo atual em strings de hora e data legíveis
		strftime(horaString, sizeof(horaString), "%H:%M:%S", tempoInfo); // Formato de hora (hh:mm:ss)
		strftime(dataString, sizeof(dataString), "%d/%m/%Y", tempoInfo); // Formato de data (dd/mm/yyyy)
		
		limparTela(); // Limpa a tela do console após exibir informações do sistema no console
		printf("\n\t\t\t\t\tSISTEMA DE CADASTRO DE VEÍCULOS\n");
		printf("%s\t\t\t\t\tProjeto SDAK\t\t\t\t\t%s\n", horaString, dataString);
		printf("----------------------------------------------------------------------------------------------------------");
		printf("\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Define a cor do texto do console como vermelho.
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Redefine as propriedades de texto para os valores padrão
        printf("--------------------------------------------------- MENU -------------------------------------------------");
		printf("\n1 - Adicionar registro\t\t4 - Apagar registro\t\t\t7 - Pesquisar históricos\n");
		printf("2 - Listar registros\t\t5 - Contar registros de hoje\t\t8 - Ler informação da placa\n");
		printf("3 - Editar registro\t\t6 - Contar registros em uma data\t9 - Encerrar\n");
		printf("----------------------------------------------------------------------------------------------------------\n");
		printf("\a\t\a\t\aEscolha uma opção: \a");
        scanf("%d", &opcao); // Lê a opção do menu
        getchar(); // Limpar o buffer de entrada
        limparTela(); // Limpar a tela

        switch (opcao) { // Executa a ação correspondente à opção escolhida
            case 1:
                adicionarRegistro(); // Chama a função para adicionar um registro
                break;
            case 2:
                listarRegistros(); // Chama a função para listar registros
                break;
            case 3:
                editarRegistro(); // Chama a função para editar um registro
                break;
            case 4:
                apagarRegistro(); // Chama a função para apagar um registro
                break;
            case 5:
                contarRegistrosHoje(); // Chama a função para contar registros de hoje
                break;
            case 6:
                contarRegistrosData(); // Chama a função para contar registros em uma data
                break;
            case 7:
                pesquisarHistoricos(); // Chama a função para pesquisar históricos
                break;
            case 8:
                lerInformacaoPlaca(); // Chama a função para ler informações da placa do veículo
                break;
            case 9:
                exit(0); // Encerra o programa
            default:
                printf("\t\aOpção inválida!\a\n"); // Mensagem para opção inválida
                Sleep(1300);
                break;
        }
    }
    return 0; // Retorna 0 para indicar o encerramento bem-sucedido do programa
} //fim da função main