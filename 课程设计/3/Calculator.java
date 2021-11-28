import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.MathContext;
import java.util.*;

public class Calculator
{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String expression = scanner.next();
        try {
            String ans = "" + SyntaxTree.calculate(expression).doubleValue();
            System.out.println(ans.replaceAll("\\.0$", ""));
        }
        catch (Exception e) {
            String error = e.toString();
            System.out.println(error.substring(20));
        }
    }
}

class SyntaxTree {
    public static BigDecimal calculate(String expression) throws Exception {
        return new SyntaxTree(parseExpr(expression)).eval();
    }

    private static Node parseExpr(String expr) throws Exception {
        debug("parseExpr", expr);
        return parseAddi(expr);
    }
    final static boolean debug = false;
    private static void debug(String p, String s) {
        if (debug) { System.out.println(p+" -> "+s); }
    }

    final protected static String PI = "p";
    final protected static String E = "e";

    private Node root;

    private SyntaxTree(Node root) {
        this.root = root;
    }

    public String toString() {
        return root.toString();
    }

    public BigDecimal eval() throws Exception {
        return root.eval();
    }

    private static int index(String s, char c) {
        int paren = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s.charAt(i) == ')') {
                paren++;
            } else if (s.charAt(i) == '(') {
                paren--;
            } else if (paren == 0 && s.charAt(i) == c) {
                return i;
            }
        }
        return -1;
    }

    private static boolean isUnaryOp(char c) { return c=='+'||c=='-'; }
    private static boolean isAlpha(char c) { return c>='a'&&c<='z'; }
    private static boolean isConst(char c) { return c=='e'||isUnaryOp(c)||isNumber(c); }
    private static boolean isNumber(char c) { return c=='.'||c=='e'||c=='p'||(c>='0'&&c<='9'); }

    private static Node parseAddi(String s) throws Exception {
        debug("parseAddi", s);
        int lastPlus = index(s, '+'), lastMinu = index(s, '-');
        if (lastPlus > 0 && s.charAt(lastPlus - 1) == 'e') {
            if (lastPlus > 1 && isNumber(s.charAt(lastPlus - 2))) {
                lastPlus = -1;
            }
        }
        if (lastMinu > 0 && s.charAt(lastMinu - 1) == 'e') {
            if (lastMinu > 1 && isNumber(s.charAt(lastMinu - 2))) {
                lastMinu = -1;
            }
        }
        if (lastPlus == -1 && lastMinu == -1) {
            return parseMult(s);
        }
        if (lastPlus > lastMinu) {
            return new Plus(parseAddi(s.substring(0, lastPlus)), parseMult(s.substring(lastPlus + 1)));
        } else {
            return new Minus(parseAddi(s.substring(0, lastMinu)), parseMult(s.substring(lastMinu + 1)));
        }
    }

    private static Node parseMult(String s) throws Exception {
        debug("parseMult", s);
        int lastMult = index(s, '*'), lastDivi = index(s, '/'), lastModu = index(s, '%');
        if (lastMult == -1 && lastDivi == -1 && lastModu == -1) {
            return parsePower(s);
        }
        int maxIndex = Math.max(lastMult, Math.max(lastDivi, lastModu));
        if (lastMult == maxIndex) {
            return new Multiply(parseMult(s.substring(0, lastMult)), parsePower(s.substring(lastMult + 1)));
        }
        else if (lastDivi == maxIndex) {
            return new Divide(parseMult(s.substring(0, lastDivi)), parsePower(s.substring(lastDivi + 1)));
        }
        else {
            return new Modulo(parseMult(s.substring(0, lastModu)), parsePower(s.substring(lastModu + 1)));
        }
    }

    private static Node parsePower(String s) throws Exception {
        debug("parsePower", s);
        int lastPower = index(s, '^');
        if (lastPower == -1) {
            return parsePrim(s);
        }
        return new Power(parsePower(s.substring(0, lastPower)), parsePrim(s.substring(lastPower + 1)));
    }
    private static Node parsePrim(String s) throws Exception {
        debug("parsePrim", s);
        if (s.length() == 0) { return new Null(); }
        for (int i=0; i<s.length(); i++) {
            if (! isConst(s.charAt(i))) { return parseFunc(s); }
        }
        return parseCons(s);
    }
    private static Node parseCons(String s) throws Exception {
        debug("parseCons", s);
        if (s.equals("e")) { return new E(); }
        if (s.equals("p")) { return new Pi(); }
        int lastE = index(s, 'e');
        if (lastE == -1) { return new Node(s, new BigDecimal(s)); }
        return new Exp(parseCons(s.substring(0, lastE)), parsePrim(s.substring(lastE+1)));
    }
    private static Node parseFunc(String s) throws Exception {
        debug("parseFunc", s);
        if (s.charAt(s.length()-1) == '!') {
            return new Factorial(parsePrim(s.substring(0, s.length()-1)));
        }
        else if (isAlpha(s.charAt(0))) {
            int pos;
            for (pos=1; pos<s.length(); pos++) {
                if (! isAlpha(s.charAt(pos))) { break ; }
            }
            String funcName = s.substring(0, pos);
            if (s.charAt(pos)!='(' || s.charAt(s.length()-1)!=')') {
                throw new Exception("�﷨����");
            }
            Node val = parseExpr(s.substring(pos+1, s.length()-1));
            if (funcName.equals("sin")) { return new Sin(val); }
            else if (funcName.equals("cos")) { return new Cos(val); }
            else if (funcName.equals("tan")) { return new Tan(val); }
            else if (funcName.equals("arcsin")) { return new Arcsin(val); }
            else if (funcName.equals("arccos")) { return new Arccos(val); }
            else if (funcName.equals("arctan")) { return new Arctan(val); }
            else if (funcName.equals("sqrt")) { return new Sqrt(val); }
            else if (funcName.equals("lg")) { return new Lg(val); }
            else if (funcName.equals("ln")) { return new Ln(val); }
            else { throw new Exception("δ֪������"); }
        }
        else {
            if (s.charAt(0)!='(' || s.charAt(s.length()-1)!=')') {
                throw new Exception("�����������У�");
            }
            return parseExpr(s.substring(1, s.length()-1));
        }
    }
}

// �ڵ�
class Node {
    private String name = "";
    private BigDecimal val = BigDecimal.ZERO;
    protected Node() {}
    protected Node(String name) { this.name = name; }
    protected Node(String name, BigDecimal val) {
        this.name = name;
        this.val = val;
    }
    public String toString() { return this.name; }
    public BigDecimal eval() throws Exception { return this.val; }
}

// �����ڵ�
class Null extends Node {}
class Pi extends Node {
    Pi() { super("p", new BigDecimal(Math.PI)); }
}
class E extends Node {
    E() { super("e", new BigDecimal(Math.E)); }
}

// ��Ԫ����
class BinOp extends Node {
    protected Node lhs, rhs;
    protected BinOp(Node lhs, String name, Node rhs) {
        super(name);
        this.lhs = lhs;
        this.rhs = rhs;
    }
    public String toString() {
        return "("+lhs.toString()+this.toString()+rhs.toString()+")";
    }
}
class Plus extends BinOp {
    protected Plus(Node lhs, Node rhs) {
        super(lhs, "+", rhs);
    }
    public BigDecimal eval() throws Exception {
        return lhs.eval().add(rhs.eval());
    }
}
class Minus extends BinOp {
    protected Minus(Node lhs, Node rhs) {
        super(lhs, "-", rhs);
    }
    public BigDecimal eval() throws Exception {
        return lhs.eval().subtract(rhs.eval());
    }
}
class Multiply extends BinOp {
    protected Multiply(Node lhs, Node rhs) {
        super(lhs, "*", rhs);
    }
    public BigDecimal eval() throws Exception {
        return lhs.eval().multiply(rhs.eval());
    }
}
class Divide extends BinOp {
    protected Divide(Node lhs, Node rhs) {
        super(lhs, "/", rhs);
    }
    public BigDecimal eval() throws Exception {
        try {
            return lhs.eval().divide(rhs.eval(), MathContext.DECIMAL128);
            // return lhs.eval().divide(rhs.eval(), 30, BigDecimal.ROUND_HALF_UP);
        }
        catch (Exception e) {
            if (e.toString().equals("java.lang.ArithmeticException: Division by zero")) {
                throw new Exception("���ܳ���0��");
            }
            else { throw e; }
        }
    }
}
class Modulo extends BinOp {
    protected Modulo(Node lhs, Node rhs) {
        super(lhs, "%", rhs);
    }
    public BigDecimal eval() throws Exception {
        try {
            return lhs.eval().divideAndRemainder(rhs.eval())[1];
        }
        catch (Exception e) {
            if (e.toString().equals("java.lang.ArithmeticException: Division by zero")) {
                throw new Exception("���ܶ�0ȡģ��");
            }
            else { throw e; }
        }
    }
}
class Exp extends BinOp {
    protected Exp(Node lhs, Node rhs) {
        super(lhs, "e", rhs);
    }
    public BigDecimal eval() throws Exception {
        try {
            return lhs.eval().multiply(new BigDecimal(Math.pow(10, rhs.eval().doubleValue())));
        } catch (Exception e) {
            throw e;
        }
    }
}
class Power extends BinOp {
    protected Power(Node lhs, Node rhs) {
        super(lhs, "^", rhs);
    }
    public BigDecimal eval() throws Exception {
        try {
            return new BigDecimal(Math.pow(lhs.eval().doubleValue(), rhs.eval().doubleValue()));
        }
        catch (Exception e) {
            if (e.toString().equals("java.lang.NumberFormatException: Infinity or NaN: Infinity")) {
                throw new Exception("0û�е�����");
            }
            else { throw e; }
        }
    }
}

// ����
class  Function extends Node {
    protected Node val;
    protected Function(String name, Node val) throws Exception {
        super(name);
        if (val instanceof Null) {
            throw new Exception("������������Ϊ�գ�");
        }
        this.val = val;
    }
    public String toString() { return this.toString()+"("+val.toString()+")"; }
}
class Sin extends Function {
    protected Sin(Node val) throws Exception { super("sin", val); }
    public BigDecimal eval() throws Exception {
        return new BigDecimal(Math.sin(val.eval().doubleValue()));
    }
}
class Cos extends Function {
    protected Cos(Node val) throws Exception { super("cos", val); }
    public BigDecimal eval() throws Exception {
        return new BigDecimal(Math.cos(val.eval().doubleValue()));
    }
}
class Tan extends Function {
    protected Tan(Node val) throws Exception { super("tan", val); }
    public BigDecimal eval() throws Exception {
        return new BigDecimal(Math.tan(val.eval().doubleValue()));
    }
}
class Arcsin extends Function {
    protected Arcsin(Node val) throws Exception { super("arcsin", val); }
    public BigDecimal eval() throws Exception {
        return new BigDecimal(Math.asin(val.eval().doubleValue()));
    }
}
class Arccos extends Function {
    protected Arccos(Node val) throws Exception { super("arccos", val); }
    public BigDecimal eval() throws Exception {
        return new BigDecimal(Math.acos(val.eval().doubleValue()));
    }
}
class Arctan extends Function {
    protected Arctan(Node val) throws Exception { super("arctan", val); }
    public BigDecimal eval() throws Exception {
        return new BigDecimal(Math.atan(val.eval().doubleValue()));
    }
}
class Sqrt extends Function {
    protected Sqrt(Node val) throws Exception { super("sqrt", val); }
    public BigDecimal eval() throws Exception {
        BigDecimal raw = val.eval();
        if (raw.compareTo(BigDecimal.ZERO) < 0) {
            throw new Exception("����û��ƽ������");
        }
        return new BigDecimal(Math.sqrt(raw.doubleValue()));
    }
}
class Lg extends Function {
    protected Lg(Node val) throws Exception { super("lg", val); }
    public BigDecimal eval() throws Exception {
        return new BigDecimal(Math.log10(val.eval().doubleValue()));
    }
}
class Ln extends Function {
    protected Ln(Node val) throws Exception { super("ln", val); }
    public BigDecimal eval() throws Exception {
        return new BigDecimal(Math.log(val.eval().doubleValue()));
    }
}
class Factorial extends Function {
    protected Factorial(Node val) throws Exception { super("!", val); }
    public String toString() { return "("+val.toString()+")!"; }
    public BigDecimal eval() throws Exception {
        BigDecimal raw = val.eval();
        if (raw.stripTrailingZeros().scale() > 0) {
            throw new Exception("ֻ�зǸ��������Խ׳ˣ�");
        }
        BigInteger value = raw.toBigInteger();
        BigDecimal res = BigDecimal.ONE;
        BigInteger i = BigInteger.ONE;
        for (; i.compareTo(value)<=0; i=i.add(BigInteger.ONE)) {
            res = res.multiply(new BigDecimal(i));
        }
        return res;
    }
}
