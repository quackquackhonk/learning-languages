
class FizzBuzz {

    public static void main(String args[]) {

        if (args.length < 1) {
            System.out.println(Integer.toString(args.length));
            System.out.println("Usage: ./fizzbuzz <num>");
        }
        else {
            int high = Integer.parseInt(args[0]);
            for (int ii = 1; ii <= high; ii++) {
                String aa = "";
                if (ii % 3 == 0) {
                    aa += "fizz";
                }
                if (ii % 5 == 0) {
                    aa += "buzz";
                }

                if (!aa.equals("")) {
                    System.out.println(aa);
                } else {
                    System.out.println(Integer.toString(ii));
                }
            }
        }

    }

}