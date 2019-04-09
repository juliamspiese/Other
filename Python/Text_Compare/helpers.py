from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    global set_a
    global set_b
    x = []
    y = []
    for i in range(len(a)):
        x.append(a.split("\n"))
    set_a = set(x)
    for i in range(len(b)):
        y.append(b.split("\n"))
    set_b = set(y)
    return set_a & set_b

def sentences(a, b):
    """Return sentences in both a and b"""
    global set_a
    global set_b
    x = []
    y = []
    for i in range(len(a)):
        x.append(sent_tokenize(a))
    set_a = set(x)
    for i in range(len(b)):
        y.append(sent_tokenize(a))
    set_b = set(y)
    return set_a & set_b

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    global set_a
    global set_b
    x = []
    y = []
    for i in range(len(a) - n + 1):
        x.append(a[i:i+n])
    set_a = set(x)
    for j in range(len(b) - n + 1):
        y.append(b[i:i+n])
    set_b = set(y)
    return set_a & set_b