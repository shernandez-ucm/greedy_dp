#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Item {
  public:
    int id;
    int value;
    int weight;
    float value_weight{0.0};
    
    Item(int i,int v,int w){
      id=i;
      value=v;
      weight=w;
      if (w!=0){
        value_weight=1.0*v/w;
      }
      else{
        value_weight=v;
      }
    }
    void display() const{
      std::cout << "id: " << id << ",value: " << value << ",weight : "<< weight <<"\n";
    }
   
};

// Función para exportar el heap a formato DOT
void export_heap_to_dot(const std::vector<Item>& heap, const std::string& filename) {
  std::ofstream file(filename);
  file << "digraph G {\n";
  file << "  node [shape=circle];\n";
  for (size_t i = 0; i < heap.size(); ++i) {
      file << "  " << i << " [label=\""  << heap[i].value_weight << "\"];\n";
      size_t left = 2 * i + 1;
      size_t right = 2 * i + 2;
      if (left < heap.size())
          file << "  " << i << " -> " << left << ";\n";
      if (right < heap.size())
          file << "  " << i << " -> " << right << ";\n";
  }
  file << "}\n";
  file.close();
}

int main() {
  // https://developers.google.com/optimization/pack/knapsack?hl=es-419#c++
  std::vector<int> values = {
      360, 83, 59,  130, 431, 67, 230, 52,  93,  125, 670, 892, 600,
      38,  48, 147, 78,  256, 63, 17,  120, 164, 432, 35,  92,  110,
      22,  42, 50,  323, 514, 28, 87,  73,  78,  15,  26,  78,  210,
      36,  85, 189, 274, 43,  33, 10,  19,  389, 276, 312};

  std::vector<int> weights = {7,  0,  30, 22, 80, 94, 11, 81, 70, 64, 59, 18, 0,  36, 3,  8,  15,
       42, 9,  0,  42, 47, 52, 32, 26, 48, 55, 6,  29, 84, 2,  4,  18, 56,
       7,  29, 93, 44, 71, 3,  86, 66, 31, 65, 0,  79, 20, 65, 52, 13};

  std::vector<int> packed_weights;
  std::vector<int> packed_items;

  int capacity = 850;
  std::vector<Item> all_items;
  for (int i=0;i<values.size();i++){
    Item item(i,values[i],weights[i]);
    all_items.push_back(item);
  }
  auto compareByValueWeight = [](const Item &a,const Item &b) {
      return a.value_weight < b.value_weight;
  };
  auto compareByValue = [](const Item &a,const Item &b) {
    return a.value < b.value;
  };
  std::make_heap(all_items.begin(), all_items.end(),compareByValueWeight);
  int sum_weights=0;
  int sum_values=0;
  int i=0;
  while (all_items.size()>0){
    std::string filename;
    filename = "heap_" + std::to_string(i) + ".dot";
    export_heap_to_dot(all_items, filename);
    std::pop_heap(all_items.begin(),all_items.end(),compareByValueWeight);
    Item item = all_items.back();
    all_items.pop_back();
    if (item.weight<=capacity-sum_weights){
      sum_values+=item.value;
      sum_weights+=item.weight;
      packed_items.push_back(item.id);
      packed_weights.push_back(item.weight); 
    }   
    i+=1;
  }
  std::sort(packed_items.begin(), packed_items.end());
  std::cout << "Total value : "<< sum_values << ", Total weights: " << sum_weights << "\n";
  std::cout << "Packed items: [";
  for (const auto i : packed_items) { std::cout << i << ","; }
  //std::cout << "]";
  return 0;
  
}
