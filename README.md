# Fundamentos de Sistemas Embarcados - Projeto 2
## Integrantes
| Matrícula | Aluno |
| -- | -- |
| 17/0114040  |  Samuel de Souza Buters Pereira |

## Compilação
### Servidor Central
Para a compilação do servidor central, vá até o diretório CentralServer e execute:
> make all

O projeto será compilado no arquivo central_server.bin que estará na mesma pasta. <br>

Logo, após a compilação, para executar o projeto, execute:
> ./central_server.bin

Para limpar o diretório, execute:
> make clean

### Servidor Distribuído
Para a compilação do servidor distribuído, vá até o diretório DistributedServer e execute:
> make all

O projeto será compilado no arquivo distributed_server.bin que estará na mesma pasta. <br>

Logo, após a compilação, para executar o projeto, execute:
> ./distributed_server.bin

Para limpar o diretório, execute:
> make clean

## Uso
### Servidor Central
Ao executar o projeto em junção com o servidor distribuído, uma interface será apresentada ao usuário. <br>

É possível visualizar todas as entradas e saídas as quais serão atualizadas em tela a cada 1 segundo. <br>

Ao apertar enter, o usuário pode mudar o estado de alguma saída como também ativar o alarme, voltando em seguida para o menu principal. <br>

Pressionar a tecla 1 trará o usuário para uma lista de saídas a qual pode mudar o valor pressionando a tecla correspondente a cada um, sem necessidade de apertar Enter. <br>

Pressionar a tecla 2 ativará/desativará o alarme de acordo com o seu estado atual. <br>

Cada evento é registrado e ao encerramento do programa (Ctrl + C), estes estarão presentes no arquivo data.csv no diretório do servidor central. <br>

Ao executar o projeto, é possível escolher a fonte da temperatura referencial a partir do menu inicial. <br>

### Servidor Distribuído
Ao executar o projeto em junção com o servidor central, o servidor distribuído fornecerá os dados iniciais das entradas e saídas ao servidor central, como também receberá e tratará requisições por consulta de dados de temperatura e umidade, como também requisição de mudança de estados de saídas. <br>

Não há uma interface como no servidor central. <br>

Para encerrar a execução, utiliza CTRL + C. <br>

## Outros
Existe um timeout para a conexão entre os servidores, sendo feitas cinco tentativas de conexão com um intervalo de um segundo entre elas e, caso não consiga ser feito essa conexão (por exemplo, caso o outro servidor não tenha sido subido), o programa será encerrado. <br>

No socket.h é possível mudar o IP e a porta do servidor a qual o servidor o qual está executando irá se comunicar, como também a porta a qual irá escutar por conexões.
