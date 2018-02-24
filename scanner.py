class Scanner():
    
    def __init__(self, arq):
        self.EoF = "\uffff"
        self.linha = 1
        self.coluna = 0
        self.caracter = " "
        self.arquivo = arq

    def scan(self):
        conteudo = self.arquivo.read()
        for letra in conteudo:
            print(letra)