// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
#include <string>
#include <iostream>
#include <vector>
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    void findRecipeName(const std::string& name) const {
        for (const auto& recipe : recipes) {
            if (recipe.potionName == name) {
                std::cout << "\n>> 물약 '" << recipe.potionName << "'의 레시피:" << std::endl;
                std::cout << " 필요 재료: ";
                for (size_t i = 0; i < recipe.ingredients.size(); ++i) {
                    std::cout << recipe.ingredients[i];
                    if (i < recipe.ingredients.size() - 1) std::cout << ", ";
                }
                std::cout << "\n" << std::endl;
                return;
            }
        }
        std::cout << ">> '" << name << "'에 대한 레시피를 찾을 수 없습니다.\n" << std::endl;
    }

    void findRecipesIngredient(const std::string& ingredient) const {
        bool found = false;
        std::cout << "\n>> 재료 '" << ingredient << "'가 포함된 레시피 목록:" << std::endl;

        for (const auto& recipe : recipes) {
            for (const auto& ingr : recipe.ingredients) {
                if (ingr == ingredient) {
                    std::cout << "- " << recipe.potionName << " (필요 재료: ";
                    for (size_t i = 0; i < recipe.ingredients.size(); ++i) {
                        std::cout << recipe.ingredients[i];
                        if (i < recipe.ingredients.size() - 1) std::cout << ", ";
                    }
                    std::cout << ")" << std::endl;
                    found = true;
                    break; 
                }
            }
        }

        if (!found) {
            std::cout << "해당 재료를 포함하는 레시피가 없습니다.\n" << std::endl;
        }
    }

};

int main() {
    AlchemyWorkshop myWorkshop;

    while (true) {
        std::cout << "⚗️ 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 검색" << std::endl;
        std::cout << "4. 재료로 검색" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);
                if (ingredient == "끝") break;
                ingredients_input.push_back(ingredient);
            }

            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) {
            std::string searchName;
            std::cout << "검색할 물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, searchName);
            myWorkshop.findRecipeName(searchName);

        }
        else if (choice == 4) {
            std::string searchIngredient;
            std::cout << "검색할 재료 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, searchIngredient);
            myWorkshop.findRecipesIngredient(searchIngredient);

        }
        else if (choice == 5) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}