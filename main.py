import sys

def error(e):
    print('ERRO: {}'.format(e))
    exit(-1)


if __name__ == "__main__":
    if(len(sys.argv) < 2):
        print("Informe o arquivo para ser compilado")
    else:
        arquivo = sys.argv[1]
        print("abrindo: {}".format(arquivo))
        
        try:
            f = open(arquivo, 'r')
        except FileNotFoundError as e:
            error(e)
