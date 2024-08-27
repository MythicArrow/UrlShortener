#include <iostream>
#include <unordered_map>
#include <string>
#include <random>
#include <regex>

// Function to generate a short code for the URL
std::string generateShortCode(int length = 6) {
    std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);
    
    std::string shortCode;
    for (int i = 0; i < length; ++i) {
        shortCode += characters[distribution(generator)];
    }
    return shortCode;
}

// Storage for the URL mappings
std::unordered_map<std::string, std::string> urlMap;

// Function to store the mapping of short code to the original URL
void storeURL(const std::string& shortCode, const std::string& originalURL) {
    urlMap[shortCode] = originalURL;
}

// Function to retrieve the original URL from a short code
std::string getOriginalURL(const std::string& shortCode) {
    if (urlMap.find(shortCode) != urlMap.end()) {
        return urlMap[shortCode];
    } else {
        return "URL not found!";
    }
}

// Function to create a short URL from the original URL
std::string createShortURL(const std::string& originalURL) {
    std::string shortCode = generateShortCode();
    storeURL(shortCode, originalURL);
    return "https://short.url/" + shortCode;
}

// Function to retrieve the original URL from a short URL
std::string redirectToOriginalURL(const std::string& shortURL) {
    std::string shortCode = shortURL.substr(shortURL.find_last_of("/") + 1);
    return getOriginalURL(shortCode);
}

// Function to validate URL format
bool isValidURL(const std::string& url) {
    const std::regex urlPattern(R"((http|https)://[a-zA-Z0-9./?=_-]+)");
    return std::regex_match(url, urlPattern);
}

int main() {
    std::string userInput;
    int choice;

    while (true) {
        std::cout << "1. Shorten URL\n";
        std::cout << "2. Retrieve Original URL\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Ignore leftover newline character

        if (choice == 1) {
            std::cout << "Enter the URL to shorten: ";
            std::getline(std::cin, userInput);
            if (isValidURL(userInput)) {
                std::string shortURL = createShortURL(userInput);
                std::cout << "Shortened URL: " << shortURL << std::endl;
            } else {
                std::cout << "Invalid URL format. Please enter a valid URL starting with http:// or https://.\n";
            }
        } else if (choice == 2) {
            std::cout << "Enter the short URL to retrieve: ";
            std::getline(std::cin, userInput);
            if (userInput.find("https://short.url/") == std::string::npos) {
                std::cout << "Invalid short URL format. Please make sure it starts with https://short.url/.\n";
                continue;
            }
            std::string originalURL = redirectToOriginalURL(userInput);
            std::cout << "Original URL: " << originalURL << std::endl;
        } else if (choice == 3) {
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
