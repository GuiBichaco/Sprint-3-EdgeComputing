``` Projeto para a matéria de Edge computing e computer Systems da faculdade FIAP - para o trabalho Challenge 2023 em conjunto e parceria com a IBM 

**APLICAÇÃO IoT - SMART LIGHT**

Explicação em vídeo --> [https://youtu.be/8qjg8Afi5yQ?si=TJqOuGgNcurKtx8h]

Nós, desenvolvedores e fundadores da Smart Light, projetamos uma IoT cujo objetivo é medir a distância em um meio físico usando um circuito com um sensor ultrassônico e um protocolo de comunicação MQTT, Cloud Service e Portas Seriais. Todo esse ecossistema pode ser conectado de forma sincronizada, desde a placa até o fluxo de recebimento do sinal e até o painel de controle via MQTT.

Essa aplicação pode ser facilmente projetada por pessoas fora da área com esta documentação.

Em caso de ter os sistemas listados em sua máquina no site dos mesmos, é de fácil compreensão a instalação.


Conceito de IoT:

A Internet das Coisas (IoT) é uma rede de objetos físicos com sensores e conectividade à internet, que coletam dados do ambiente ou do próprio dispositivo e os enviam para servidores ou outros dispositivos para tomada de decisões. A IoT desempenha um papel importante em áreas como automação, saúde, sustentabilidade e cidades inteligentes, melhorando a eficiência e a qualidade de vida da sociedade.

**-> Arduino IDE**

Com o software Arduino IDE, você deverá desenvolver seu código de acordo com o uso da sua placa. A linguagem adequada é o C++ (nossos códigos-fonte estarão mais abaixo desta documentação). A plataforma Arduino IDE é responsável pela compilação do código programado para o seu circuito em C++ para ser lido pela firmware da placa.

Ao terminar o código, vá em "Verify", "Sketch", "Export Compiled Binary". Logo em seguida, vá em "File", "Save As" e salve o arquivo no local desejado.

**-> SimulIDE**

Caso você não tenha condições de adquirir o kit Arduino para você, a plataforma SimulIDE é a solução. Sendo um simulador de circuito gratuito e muito completo, nós estruturamos nosso circuito nele, onde conectamos um voltímetro para medir a distância no sensor ultrassônico na placa Arduino Uno, que está conectada a uma porta serial, a qual faz a conexão com o Node-Red.

Para carregar seu código compilado no Arduino IDE na placa, clique com o botão direito sobre a placa Arduino Uno, vá em "Load Firmware". Abrirá o seletor de arquivos. Vá até o local da pasta onde você salvou seu projeto do Arduino IDE, entre em "build", depois em "arduino.avr.uno". O arquivo que você deve carregar na placa sempre será o com o nome do projeto do Arduino IDE com a extensão .ino.hex seguindo este modelo: nomeDoProjeto.ino.hex. MUITA ATENÇÃO!!

**-> com0com**

Na plataforma com0com, você fará a abertura das portas de comunicação em sua máquina (servidor local). Elas são chamadas de portas seriais. Essas portas seriais serão responsáveis por conectar o circuito do SimulIDE com o fluxo do Node-Red, que será explicado em breve. É necessário fazer o download desse sistema com muita atenção, pois o driver para abrir essas portas seriais não é baixado diretamente, e sim você deve selecionar se quer ou não, geralmente é um checkbox escrito COM.

**-> Node-Red**

Ele será responsável pela construção do fluxo do servidor local, onde conecta todos os passos até aqui em um único nó de conexão. Via protocolo de comunicação MQTT, ele será conectado a um servidor aberto chamado Tago para a construção das devices e do dashboard.

A instalação do Node-Red é simples:

- Faça a instalação do Node.js (Versão LTS) (node-version) - [www.nodejs.org](www.nodejs.org)
- Abra o CMD e digite (npm install -g --unsafe-perm node-red)
- Para acessar o serviço, após instalado, digite no cmd: node-red
- Acesse no browser: [http://localhost:1880](http://localhost:1880)

Após abrir o programa, vá nas três barrinhas no canto superior direito, "Gerenciar Paletas" e baixe a biblioteca node-red-node-serialport.

Logo em seguida, encontre o nó "Serial In" para a configuração da porta serial. Adicione a porta no lápis de edição, colocando o nome correto da mesma e configure o Baud Rate para 9600. Pronto, só implementar.

Coloque o nó de análise semântica JSON, para que as informações recebidas da porta COM sejam convertidas em formato JSON. Conecte esse nó ao nó de DEBUG para visualizações de possíveis erros.

Acrescente o nó de função e configure as variáveis da seguinte maneira:

```javascript
var currentDate = new Date();

var B = {
    payload: {
        "variable": "distancia",
        "unit": "centímetros",
        "value": msg.payload.distance.toString(),
    }
};

return B;
```

Por fim, conecte tudo ao nó MQTT Out. Mas antes, vamos ao tago.io.

**-> Tago.io**

- Crie uma conta na Tago.
- Vá em "Devices", "Custom MQTT" (Crie um nome para o mesmo em "Device Name").
- Clique em "Create My Device", espere carregar e finalize.
- Localize a sua device, encontre um ícone de olho próximo à área de Token e número de série (serial number). Ele irá revelar o seu token.
- Copie o seu Token e volte ao Node-Red.

Pronto, o resultado esperado será uma IoT operacional apresentando seus valores no dashboard de forma exata.

Para dúvidas, contate a equipe técnica:

- Enzo de Oliveira Cunha - 550985
- Guilherme Catelli Bichaco - 97989
- Lucas Almeida de Siqueira - 551854
- Lucas Laia Manentti - 97709
- Vinicius Sobreira Borges - 97767
