public class Estabelecimentos {
    private String nome;
    private Integer preco;
    private Integer vezesCompradas;

    public String getNome() {
        return nome;
    }
    public Integer getPreco() {
        return preco;
    }
    public Integer getVezesCompradas() {
        return vezesCompradas;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
    public void setPreco(Integer preco) {
        this.preco = preco;
    }
    public void setVezesCompradas(Integer vezesCompradas) {
        this.vezesCompradas = vezesCompradas;
    }

    public Estabelecimentos(String nome, Integer preco) {
        this.vezesCompradas = 0;
        this.nome = nome;
        this.preco = preco;
    }
}
