#Introdução
O objetivo deste trabalho é desenvolver um sistema de comunicação bidirecional entre um
Arduino e um PC utilizando o display LCD 16x2 e dois pushbuttons. O sistema permitirá ao
usuário escolher entre duas opções principais: enviar uma mensagem do Arduino para o PC
ou receber uma mensagem do PC no Arduino.

Este projeto pode ser dividido em duas partes principais:

1) Comunicação Arduino-Computador: Vocês precisarão escrever dois códigos (um para
o Arduino e outro para o Computador) que estabeleça uma comunicação serial entre o
Arduino e o computador. Os códigos deverão ser capazes de enviar e receber
informações entre os dois dispositivos.

2) Exibição/Controle de mensagens em display LCD 16x2: O código do Arduino deverá
ser capaz de exibir mensagens na tela do LCD e, através dos pushbuttons, escrever
mensagens.

(mais informações abaixo).

#Definições
Equipamento (device): Dispositivo de eletrônica embarcada dotado de um microcontrolador
programável (em linguagem C), algum dispositivo de comunicação serial e interfaces de
entrada e saída (Ex. Arduino Uno). A este dispositivo deverá estar conectado um display
para exibição de mensagens de texto que deve ser capaz de exibir, no mínimo, 16 caracteres
por linha e ter, no mínimo, duas linhas para mensagens (Ex. display LCD 16x2).
Interface (cliente ou estação): Software desenvolvido em linguagem C que “rodará” em um
PC (Computador Pessoal), servirá para enviar e receber as informações dos equipamentos.

#Especificações
Este documento traz as especificações referentes ao trabalho da disciplina de Programação
Aplicada do semestre de 2024/1. As informações aqui contidas servirão como base para o
desenvolvimento do trabalho pelos alunos. Além de seguirem os critérios aqui descritos,
os grupos deverão abordar o maior número de conceitos vistos em sala de aula possível,
sendo esses conceitos levados em consideração durante a avaliação do projeto.

A Interface
A interface deverá ser desenvolvida em linguagem C e capaz de “interagir” com o usuário
através do console. Ela deverá ser dotada de “Menus” de navegação, de modo que o usuário
possa escolher o que deseja fazer.
Requisitos mínimos para a interface:

● Uma tela principal com o título do trabalho, nome dos integrantes e uma opção que
“avance” para a próxima tela.

● Uma tela onde o usuário selecione quem irá escrever a mensagem o PC ou o Arduino
(mais detalhes abaixo).

● Ao escolher que quem enviará a mensagem é o PC, o usuário deverá ser levado a uma
tela que peça que ele digite a mensagem (veja a seção “Critérios para as mensagens”
para obter mais informações).

● Uma vez digitada a mensagem e teclado “Enter”, a mensagem será enviada para o
Arduino e o usuário deverá ser levado de volta à tela anterior.
Critérios Para as Mensagem

● Mensagem enviada pelo PC: Estas mensagens poderão conter qualquer caractere
alfanumérico (a-z, A-Z e 0-9) e um tamanho máximo de 16 caracteres (para caber em
uma única linha do display).

● Mensagem enviada pelo Arduino: Para facilitar o “selecionar” das letras, as
mensagens enviadas do Arduino para o PC deverão conter apenas as letras a-e-i-o-u. E
a mensagem a ser enviada deve ter no mínimo 5 caracteres e, para facilitar, podem ter
um tamanho fixo (ao atingir esse tamanho o arduino pode enviar a mensagem
automaticamente). As mensagens não precisam fazer sentido, pode ser algo como
“aioeu”.

#Entrega do Projeto
● Vocês deverão entregar um relatório do projeto, incluindo a descrição do processo de
comunicação utilizado e as funcionalidades do seu código (não é preciso explicar o
código linha a linha, escreva sobre as funções que foram criadas, bibliotecas utilizadas
e os conceitos da disciplina que foram utilizados e onde foram utilizados). É
interessante ter um esquemático das ligações elétricas feitas (pode ser utilizado o
Tinkercad, veja o exemplo da Figura 6).

● Junto com o relatório deverá ser entregue os códigos desenvolvidos pelo grupo, de
preferência utilizando um sistema de repositório de código como, por exemplo, o
Github (github.com).

● O funcionamento do trabalho deverá ser apresentado presencialmente na Faculdade
UCL, vejas as datas de entrega abaixo.

Observações Importantes
● Os grupos deverão ser formados por no máximo 04 (quatro) alunos.

● A avaliação do trabalho será baseada no relatório entregue, aspectos construtivos do
equipamento, usabilidade da interface e uso dos conceitos abordados durante a
disciplina de Programação Aplicada.
o O uso das técnicas aprendidas em sala de aula representarão 50% da
composição da nota.

● Atrasos serão penalizados com a perda de dois pontos para cada fração de dia de
atraso.

● Todos os grupos deverão enviar os códigos e o relatório através do formulário
(https://forms.gle/TuABo1mJa9dQxnM56) até o dia 05/07/2024.

● As apresentações acontecerão no dia 03/07/2024 (isso mesmo, dois dias antes da data
limite para o relatório).

o No dia 03/07 acontecerá a apresentação FINAL do trabalho. Entretanto, existem
duas entregas intermediárias que os grupos precisarão estar atentos.

▪ Dia 08/05/2024: Neste dia cada grupo deverá apresentar a parte do
hardware completamente montada, e algum código no Arduino que
mostre que as funcionalidades estão OK. Por exemplo, uma mensagem
qualquer deve estar sendo exibida no display e os botões devem executar
qualquer ação que o grupo desejar.

▪ Dia 05/06/2024: Neste dia cada grupo deverá apresentar um programa
desenvolvido no PC e que já envia e/ou recebe mensagens do arduino por
meio da comunicação serial.

Um ótimo trabalho a todos!
