#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Product {
public:
    int productID;
    string name;
    string category;  // New attribute for category (Electronics or Fashion)
    float price;
    float rating;

    Product(int productID, const string& name, const string& category, float price, float rating) {
        this->productID = productID;
        this->name = name;
        this->category = category;
        this->price = price;
        this->rating = rating;
    }
};

// Comparator for sorting products by ID
bool compareByID(const Product& a, const Product& b) {
    return a.productID < b.productID;
}

class RecommendationEngine {
private:
    vector<Product> products;  // List of products
    vector<Product> cart;      // User's cart
    map<string, vector<Product>> categorizedProducts;  // Map for category-based recommendations

public:
    RecommendationEngine() {
        // Adding some products with categories and ratings
        products.push_back(Product(1, "Laptop", "Electronics", 800.50, 4.5));
        products.push_back(Product(2, "Smartphone", "Electronics", 500.00, 4.7));
        products.push_back(Product(3, "Headphones", "Electronics", 150.75, 4.3));
        products.push_back(Product(4, "Smartwatch", "Electronics", 250.00, 4.1));
        products.push_back(Product(5, "Tablet", "Electronics", 300.25, 4.6));
        products.push_back(Product(6, "Camera", "Electronics", 450.00, 4.8));
        products.push_back(Product(7, "T-shirt", "Fashion", 20.00, 4.2));
        products.push_back(Product(8, "Jeans", "Fashion", 50.00, 4.3));
        products.push_back(Product(9, "Jacket", "Fashion", 100.00, 4.5));
        products.push_back(Product(10, "Sneakers", "Fashion", 75.00, 4.4));

        // Sort products by ID for binary search
        sort(products.begin(), products.end(), compareByID);

        // Categorize products into Electronics and Fashion
        for (const auto& product : products) {
            categorizedProducts[product.category].push_back(product);
        }
    }

    void displayProducts() {
        cout << "Available products:\n";
        for (const auto& product : products) {
            cout << "ID: " << product.productID << ", Name: " << product.name
                 << ", Category: " << product.category << ", Price: $" << product.price
                 << ", Rating: " << product.rating << endl;
        }
    }

    void addToCart(int productId) {
        for (const auto& product : products) {
            if (product.productID == productId) {
                cart.push_back(product);
                cout << product.name << " added to cart." << endl;
                return;
            }
        }
        cout << "Product ID " << productId << " not found!" << endl;
    }

    // Binary search function to find a product by ID
    Product* binarySearch(int productId) {
        int left = 0;
        int right = products.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (products[mid].productID == productId) {
                return &products[mid];  // Return a pointer to the found product
            }
            if (products[mid].productID < productId) {
                left = mid + 1;  // Search in the right half
            } else {
                right = mid - 1; // Search in the left half
            }
        }
        return nullptr; // Product not found
    }

    void searchProduct(int productId) {
        Product* product = binarySearch(productId);
        if (product) {
            cout << "Found: " << product->name << " for $" << product->price << " with rating: " << product->rating << endl;
        } else {
            cout << "Product ID " << productId << " not found." << endl;
        }
    }

    void recommendProducts() {
        if (cart.empty()) {
            cout << "Your cart is empty. Please add products to your cart to get recommendations." << endl;
            return;
        }

        // Determine the category of products in the cart
        string cartCategory = cart[0].category;  // Assuming all products in the cart belong to the same category

        cout << "\nRecommended " << cartCategory << " products based on your cart:\n";

        for (const auto& product : categorizedProducts[cartCategory]) {
            // Recommend products from the same category that are not already in the cart
            bool alreadyInCart = false;
            for (const auto& cartProduct : cart) {
                if (product.productID == cartProduct.productID) {
                    alreadyInCart = true;
                    break;
                }
            }
            if (!alreadyInCart) {
                cout << "You might like: " << product.name << " for $" << product.price << " with rating: " << product.rating << endl;
            }
        }
    }

    void displayCart() {
        cout << "Items in your cart:\n";
        for (const auto& product : cart) {
            cout << "ID: " << product.productID << ", Name: " << product.name
                 << ", Category: " << product.category << ", Price: $" << product.price
                 << ", Rating: " << product.rating << endl;
        }
    }
};

int main() {
    RecommendationEngine engine;
    engine.displayProducts();

    int choice;
    while (true) {
        cout << "\nOptions:\n1. Add to Cart\n2. Search Product\n3. Recommend Products\n4. Display Cart\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int productId;
            cout << "Enter Product ID to add to cart: ";
            cin >> productId;
            engine.addToCart(productId);
        } else if (choice == 2) {
            int productId;
            cout << "Enter Product ID to search for: ";
            cin >> productId;
            engine.searchProduct(productId);
        } else if (choice == 3) {
            engine.recommendProducts();
        } else if (choice == 4) {
            engine.displayCart();
        } else if (choice == 5) {
            return 0;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
