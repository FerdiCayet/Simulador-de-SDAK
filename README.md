<h1 align="center">Projeto SDAK - Sistema de Cadastro de Veículos</h1>

<img src="https://lh3.googleusercontent.com/pw/AIL4fc8oVYkHnoSWIwYKiV5lF4haarDkrJdt_a5T4j4pxIY4c21we6JR1_dZmoa8LKycAPO-EXAvQLpTUs8nRSOTd5o5BNK92QPr_fEdRQzhXu00aoeX6eOdJxUwSr5nGSqIGuc-mMQDhqJiXreANPaZNJRV=w1200-h628-s-no" style="border-radius: 5px;" align="right" width="420">

O Projeto SDAK é uma aplicação em linguagem C que simula um sistema de cadastro de veículos, proporcionando aos usuários a capacidade de executar diversas operações relacionadas ao registro e gerenciamento de informações de veículos. Desenvolvido com o objetivo de fornecer um ambiente de aprendizado e prática, este projeto oferece uma interface de linha de comando que permite aos entusiastas de programação explorar e compreender os processos envolvidos no registro e licenciamento de veículos.

### Sobre o Projeto

O projeto consiste em um simulador do Sistema de Registro e Licenciamento de Veículos (SDAK), um sistema oficial utilizado no Estado de Minas Gerais para gerenciar o registro e licenciamento de veículos. Desenvolvido pelo Detran-MG e em operação desde 2009, o SDAK oferece uma variedade de serviços relacionados a veículos de forma online e eficiente.

### Objetivo

O objetivo deste projeto é proporcionar um ambiente de aprendizado e prática para aqueles interessados em programação em C, enquanto simulam operações importantes do SDAK. O simulador oferece uma plataforma para explorar e entender os processos de registro e licenciamento de veículos de forma prática.

### Como Utilizar

1. Clone este repositório para sua máquina local.

    ```git
    git clone https://github.com/FerdiCayet/Simulador-de-SDAK
    ```
2. Abra o ambiente de desenvolvimento C de sua preferida. Recomendamos o uso do _Dev-C++_ como uma IDE popular para desenvolvimento em C. Você pode baixá-lo [aqui](https://www.bloodshed.net/).
3. Abra o arquivo de código-fonte do projeto no ambiente de desenvolvimento C. Geralmente, os arquivos de código-fonte têm a extensão "`.c`".
4. Compile o código-fonte em seu ambiente de desenvolvimento C. Isso pode ser feito pressionando o botão "Compilar" ou usando a opção de menu apropriada em sua IDE.
5. Após a compilação bem-sucedida, você terá um arquivo executável (geralmente com extensão "`.exe`") gerado a partir do código-fonte.
6. O programa será iniciado e siga as instruções do menu para realizar operações com os registros de veículos.

### Compilando e Vinculando Recursos (Opcional)

Se desejar executar o arquivo executável com um ícone personalizado, siga os passos abaixo:

1. Compile o arquivo de recursos (`.rc`) usando `windres.exe` e gere um arquivo de recursos compilado (`.res`):

   ```shell
   windres.exe resource.rc -O coff resource.res
   ```

2. Compile o programa, incluindo o arquivo de recursos compilado, usando o GCC:

    ```shell
   gcc SeuArquivo.c resource.res -o SeuPrograma
   ```
Certifique-se de substituir "SeuArquivo.c" pelo nome do seu arquivo de código-fonte e "SeuPrograma" pelo nome desejado para o executável final.

Agora, você deve ter seu programa executável com os recursos incorporados.

3. Para iniciar o programa sem a necessidade de execução manual, você pode simplesmente clicar no arquivo `SDAK.exe`. Ele estará pronto para uso. Fique à vontade para usá-lo na sua aplicação.

### Funcionalidades Principais

Este projeto oferece as seguintes funcionalidades principais:

<details>
  <summary>Clique para expandir para descobrir mais informações sobre cada recurso.</summary>

###### O arquivo de código-fonte [main.c](https://github.com/FerdiCayet/Simulador-de-SDAK/blob/main/main.c) informa cada função com detalhes:

- **`strcasestr_custom`**

  A função `strcasestr_custom` é uma implementação personalizada da função strcasestr, que é usada para buscar uma substring (cadeia de caracteres) em uma string, sem diferenciação entre maiúsculas e minúsculas. Ela retorna um ponteiro para a primeira ocorrência da substring na string principal ou NULL se a substring não for encontrada.

- **Limpar Tela**

  Esta função é responsável por limpar a tela do console ou terminal, tornando a interface de linha de comando mais limpa e organizada. Geralmente, é usada para melhorar a legibilidade e a interação do usuário com o programa, removendo informações anteriores da tela.
  
- **Autenticar Usuário**

  A função `autenticarUsuario` é responsável por autenticar os usuários do sistema. Ela pode solicitar credenciais de acesso, como nome de usuário e senha, e verificar se essas credenciais correspondem às informações armazenadas no sistema. Se a autenticação for bem-sucedida, a função pode conceder acesso às funcionalidades principais do sistema.

- **Cadastrar Acesso**
  
  A função `cadastrarAcesso` oferece autenticação ao sistema, requerendo um código de acesso para acessar suas funcionalidades. Isso ajuda a manter a segurança do sistema e permite o controle de quem pode utilizar as funções.

- **Acessar Sistemas**
  
  A função `acessarSistemas` é responsável por verificar se o acesso ao sistema é autorizado com base no código fornecido pelo usuário. Se o código de acesso for válido, o usuário terá acesso às funcionalidades principais do sistema.

- **Adicionar Registro**
  
  A função `adicionarRegistro` permite aos usuários inserir informações detalhadas sobre um veículo, incluindo data e hora, nome do proprietário, placa, marca, modelo, cor, observações e muito mais. O registro é armazenado em um arquivo de texto.

- **Listar Registros**
  
  A função `listarRegistros` exibe todos os registros de veículos armazenados no diretório atual. Cada registro é formatado e exibido de forma legível para o usuário.

- **Editar Registro**
  
  A função `editarRegistro` permite aos usuários fazer alterações em um registro de veículo existente. Os usuários podem atualizar informações como placa, cor, proprietário, entre outras.

- **Apagar Registro**
  
  A função `apagarRegistro` permite aos usuários excluir um registro de veículo com base na placa do veículo. O registro é permanentemente removido do sistema.

- **Contar Registros de Hoje**
  
  A função `contarRegistrosHoje` exibe o número de registros de veículos criados no dia atual. Isso pode ser útil para rastrear a atividade diária.

- **Contar Registros em uma Data**
  
  A função `contarRegistrosData` permite aos usuários especificar uma data e contar o número de registros de veículos criados nessa data específica.

- **Pesquisar Históricos**
  
  A função `pesquisarHistoricos` permite aos usuários realizar pesquisas em todos os registros de veículos para encontrar ocorrências de palavras-chave específicas. Os resultados incluem informações sobre o arquivo e a linha onde a palavra-chave foi encontrada.

- **Ler Informação da Placa do Veículo**
  
  A função `lerInformacaoPlaca` permite aos usuários buscar informações específicas com base na placa de um veículo. As informações incluem detalhes como data e hora, nome do proprietário e muito mais.

- **Menu Principal**

  A função `main` é a função principal de um programa em C/C++. Ela é o ponto de entrada do programa e é executada automaticamente quando o programa é iniciado. A função main geralmente contém o código principal do programa, incluindo a chamada de outras funções e a lógica de controle do programa. É onde a execução do programa começa e termina.

###### O arquivo de código-fonte [resource.rc](https://github.com/FerdiCayet/Simulador-de-SDAK/blob/main/resource.rc):

Responsável por definir ícones utilizados na interface gráfica do programa no ambiente Windows.

- **Ícone Principal (MAINICON)**

  Este ícone, associado ao arquivo "favicon.ico", representa a identidade visual do programa e é exibido na barra de título da janela, no gerenciador de tarefas e em outros locais onde o programa é identificado.

- **Ícone Saída (EXIT_ICO)**

  Associado ao arquivo "app.ico", este ícone pode ser utilizado para diversos fins na interface do usuário, conforme necessário.

O arquivo resource.rc inclui diretivas para evitar a inclusão múltipla do arquivo.

Este arquivo é fundamental para aprimorar a experiência visual dos usuários do seu programa no Windows.

</details>

### Requisitos

Certifique-se de que seu sistema atenda aos seguintes requisitos antes de compilar e executar o programa:

1. **Sistema Operacional**: Este código-fonte é projetado para ser executado no ambiente Windows. Pode não ser compatível com sistemas operacionais diferentes, como Linux ou macOS.

2. **GCC**: Você precisará do GCC (GNU Compiler Collection) instalado em seu sistema para compilar o código-fonte em C. Você pode verificar se o GCC está instalado digitando `gcc --version` no prompt de comando.

3. **windres.exe**: O `windres.exe` é uma ferramenta que permite compilar recursos para aplicativos Windows. Certifique-se de que o `windres.exe` também esteja disponível e configurado em seu sistema para compilar os recursos.

### Nota

Lembre-se de ajustar os nomes dos arquivos e caminhos conforme necessário para corresponder aos seus arquivos reais.

Para obter mais informações sobre como usar recursos em seu projeto, consulte a documentação relevante do GCC e do `windres.exe`.

Sinta-se à vontade para entrar em contato se você tiver alguma dúvida ou encontrar problemas durante o processo de compilação e vinculação de recursos.

<hr>
<div align="right">
    <p><i>Sistema de Cadastro de Veículos (SDAK): Eficiente, Simples e Leve.</i></p>
</div>