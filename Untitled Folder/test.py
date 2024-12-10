import random

def gerar_caso_teste_aleatorio(tipo, tamanho_a, tamanho_b, operacao, elemento=None, nome_arquivo="caso_teste.txt"):
    """
    Gera um arquivo de caso de teste aleatório para o programa principal em C.

    :param tipo: Tipo da estrutura (0 ou 1).
    :param tamanho_a: Tamanho do conjunto A.
    :param tamanho_b: Tamanho do conjunto B.
    :param operacao: Operação a ser realizada (1, 2, 3 ou 4).
    :param elemento: Elemento adicional para operações de pertinência ou remoção (opcional).
    :param nome_arquivo: Nome do arquivo de saída.
    """
    # Gera elementos aleatórios únicos para cada conjunto
    elementos_a = random.sample(range(1, 100), tamanho_a)
    elementos_b = random.sample(range(1, 100), tamanho_b)

    if operacao in [1, 4] and elemento is None:
        # Escolhe aleatoriamente um elemento do conjunto A para pertinência ou remoção
        elemento = random.choice(elementos_a)

    with open(nome_arquivo, "w") as f:
        f.write(f"{tipo}\n")
        f.write(f"{tamanho_a}\n")
        f.write(f"{tamanho_b}\n")
        f.write(" ".join(map(str, elementos_a)) + "\n")
        f.write(" ".join(map(str, elementos_b)) + "\n")
        f.write(f"{operacao}\n")
        if elemento is not None:
            f.write(f"{elemento}\n")

# Gera diferentes casos de teste com tamanhos variados
for i in range(1, 6):
    tamanho_a = random.randint(3, 10)  # Tamanho do conjunto A entre 3 e 10
    tamanho_b = random.randint(3, 10)  # Tamanho do conjunto B entre 3 e 10

    gerar_caso_teste_aleatorio(
        tipo=random.choice([0, 1]),
        tamanho_a=tamanho_a,
        tamanho_b=tamanho_b,
        operacao=1,
        nome_arquivo=f"caso_teste_{i}_pertinencia.txt"
    )

    gerar_caso_teste_aleatorio(
        tipo=random.choice([0, 1]),
        tamanho_a=tamanho_a,
        tamanho_b=tamanho_b,
        operacao=2,
        nome_arquivo=f"caso_teste_{i}_uniao.txt"
    )

    gerar_caso_teste_aleatorio(
        tipo=random.choice([0, 1]),
        tamanho_a=tamanho_a,
        tamanho_b=tamanho_b,
        operacao=3,
        nome_arquivo=f"caso_teste_{i}_interseccao.txt"
    )

    gerar_caso_teste_aleatorio(
        tipo=random.choice([0, 1]),
        tamanho_a=tamanho_a,
        tamanho_b=tamanho_b,
        operacao=4,
        nome_arquivo=f"caso_teste_{i}_remocao.txt"
    )

print("Casos de teste aleatórios gerados com sucesso!")
