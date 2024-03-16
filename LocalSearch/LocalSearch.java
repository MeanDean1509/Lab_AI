import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.function.Function;

public class LocalSearch {

    interface NSFunction extends Function<List<Integer>, List<Integer>> {}
    public static int calCost(int[][] matrix, List<Integer> path) {
        int cost = 0;

        for (int i = 0; i < path.size() - 1; i++) {
            int s = path.get(i) - 1;
            int e = path.get(i + 1) - 1;
            cost += matrix[s][e];
        }

        int s = path.get(path.size() - 1) - 1;
        int e = path.get(0) - 1;
        cost += matrix[s][e];

        return cost;
    }

    public static List<Integer> initSol(int size) {
        List<Integer> array = new ArrayList<>();

        for (int i = 1; i <= size; i++) {
            array.add(i);
        }

        Collections.shuffle(array);
        return array;
    }

    public static List<Integer> NS1(List<Integer> arr) {
        int i = new Random().nextInt(arr.size());
        int j = new Random().nextInt(arr.size());

        if (i > j) {
            int temp = i;
            i = j;
            j = temp;
        }

        List<Integer> result = new ArrayList<>(
                arr.subList(0, i)
        );
        result.addAll(
                reverseList(arr.subList(i, j + 1))
        );
        result.addAll(
                arr.subList(j + 1, arr.size())
        );

        return result;
    }

    public static List<Integer> NS2(List<Integer> arr) {
        int i = new Random().nextInt(arr.size());
        int j = new Random().nextInt(arr.size());

        List<Integer> newArray = new ArrayList<>(arr);
        int elementToInsert = newArray.remove(i);
        newArray.add(j, elementToInsert);

        return newArray;
    }

    public static List<Integer> NS3(List<Integer> arr) {
        int i = new Random().nextInt(arr.size());
        int j = new Random().nextInt(arr.size());

        if (i > j) {
            int temp = i;
            i = j;
            j = temp;
        }

        List<Integer> newArray = new ArrayList<>(arr);
        List<Integer> subArrToMove = new ArrayList<>(newArray.subList(i, j));
        int k = new Random().nextInt(newArray.size());
        newArray.addAll(k, subArrToMove);

        return newArray;
    }

    public static List<Integer> NS4(List<Integer> arr) {
        int i = new Random().nextInt(arr.size());
        int j = new Random().nextInt(arr.size());

        List<Integer> newArray = new ArrayList<>(arr);
        int temp = newArray.get(i);
        newArray.set(i, newArray.get(j));
        newArray.set(j, temp);

        return newArray;
    }

    public static List<Integer> reverseList(List<Integer> list) {
        List<Integer> reversed = new ArrayList<>(list);
        Collections.reverse(reversed);
        return reversed;
    }

    public static int[][] readFileData(String filename) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(filename));
        lines.remove(0); // Remove the first line
    
        int[][] matrix = lines.stream()
                .map(line -> line.trim().split("\\s+"))
                .map(arr -> {
                    int[] row = new int[arr.length];
                    for (int i = 0; i < arr.length; i++) {
                        row[i] = Integer.parseInt(arr[i]);
                    }
                    return row;
                })
                .toArray(int[][]::new);
    
        return matrix;
    }
    

    public static List<Integer> localSearch(List<Integer> initSolution, int[][] matrix, int maxNoImprovement, List<NSFunction> NSx) {
        List<Integer> currentSolution = new ArrayList<>(initSolution);
        int noImprovementCount = 0;

        while (noImprovementCount < maxNoImprovement) {
            for (NSFunction neighborFunction : NSx) {
                List<Integer> neighborSolution = neighborFunction.apply(currentSolution);

                if (calCost(matrix, neighborSolution) < calCost(matrix, currentSolution)) {
                    currentSolution = new ArrayList<>(neighborSolution);
                    noImprovementCount = 0;
                } else {
                    noImprovementCount++;
                }
            }
        }

        return currentSolution;
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Dang chay...");
        long startTime = System.currentTimeMillis();
        String fileName = "tsp4.txt";
        int[][] matrix = readFileData(fileName);
        int maxNoImprovement = 1000000;
        List<NSFunction> NSx = List.of(
                LocalSearch::NS1,
                LocalSearch::NS2,
                LocalSearch::NS3,
                LocalSearch::NS4
        );

        List<Integer> initSolution = initSol(matrix.length);
        List<Integer> path = localSearch(initSolution, matrix, maxNoImprovement, NSx);
        System.out.println("Duong di: " + path);
        System.out.println("Chi phi: " + calCost(matrix, path));
        long endTime = System.currentTimeMillis();
        long executionTime = endTime - startTime;
        System.out.println("Thoi gian hoan thanh: " + executionTime + " milliseconds");

        String res = "Path: " + path + "\nCost: " + calCost(matrix, path) + "\nRunning time: " + executionTime + " milliseconds";
        String[] segments = fileName.split("\\.");
        String firstSegment = segments[0];
        Files.write(Paths.get(firstSegment + "_out.txt"), res.getBytes());
    }
}
