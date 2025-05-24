#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>

using namespace std;

using Matrix = std::vector<std::vector<double>>;


Matrix readMatrix(const std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("�� ������� ������� ���� ");
    }

    Matrix matrix;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<double> row;
        double value;
        while (iss >> value) {
            row.push_back(value);
        }
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }
    return matrix;
}


void writeMatrixToFile(const Matrix& matrix, const std::string filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("�� ������� ������� ���� ��� ������ ");
    }

    for (const auto& row : matrix) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }
}


Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {

    size_t rows_A = A.size();
    size_t cols_A = A[0].size();
    size_t cols_B = B[0].size();

    Matrix result(rows_A, std::vector<double>(cols_B, 0.0));

    for (size_t i = 0; i < rows_A; ++i) {
        for (size_t j = 0; j < cols_B; ++j) {
            for (size_t k = 0; k < cols_A; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}


int main() {
    std::string matrix_A_file, matrix_B_file, matrix_result_file;


    matrix_A_file = "C:/Users/artan/OneDrive/Desktop/paralel/matrixA.txt";
    matrix_B_file = "C:/Users/artan/OneDrive/Desktop/paralel/matrixB.txt";
    matrix_result_file = "C:/Users/artan/OneDrive/Desktop/paralel/result.txt";


    Matrix A = readMatrix(matrix_A_file);
    Matrix B = readMatrix(matrix_B_file);

    if (A.empty() || B.empty()) {
        throw std::runtime_error("Matrices are empty");
    }

    auto start = chrono::high_resolution_clock::now();
    Matrix result = multiplyMatrices(A, B);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> time = end - start;


    writeMatrixToFile(result, matrix_result_file);

    ofstream fout("C:/Users/artan/OneDrive/Desktop/paralel/info.txt");
    fout << "Execution time (sec): " << time.count() << endl;
    fout.close();

    return 0;
}