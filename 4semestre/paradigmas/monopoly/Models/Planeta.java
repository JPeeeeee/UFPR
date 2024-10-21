public class Planeta {
    private String nome;
    private String tipo;
    private Integer[] hipotecas;
    private Integer contrucoes;

    public Integer getContrucoes() {
        return contrucoes;
    }
    public Integer[] getHipotecas() {
        return hipotecas;
    }
    public String getNome() {
        return nome;
    }
    public String getTipo() {
        return tipo;
    }
    public void setContrucoes(Integer contrucoes) {
        this.contrucoes = contrucoes;
    }
    public void setHipotecas(Integer[] hipotecas) {
        this.hipotecas = hipotecas;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    public Planeta(String nome, Integer[] hipotecas) {
        this.nome = nome;
        this.hipotecas = hipotecas;
        this.contrucoes = 0;
    }
}
