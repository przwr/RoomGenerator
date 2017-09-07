#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

    class ColumnBase {
      std::string m_name;
    public:
      ColumnBase(const std::string& name) : m_name(name) {}
      std::string name() { return m_name; }
    };

    template<class T>
    class Column : public ColumnBase {
      std::vector<T> m_items;
     public:
      Column(const std::string& name) :ColumnBase(name) {}
    };

    template<class... T>
    class Table {
      std::tuple<Column<T>...> m_columns;

      template<std::size_t... index>
      std::vector<ColumnBase*> columns_vec_helper(std::index_sequence<index...>) {
        return { (&std::get<index>(m_columns))... };
      }

    public:
      Table(Column<T>&&... columns) : m_columns(std::move(columns)...) {}
    
      std::vector<ColumnBase*> columns_vec() {
        return columns_vec_helper(std::make_index_sequence<sizeof...(T)>{});
      }
    };


int main() {
	Table<std::size_t, std::string, int, int> t ({"id"}, {"name"}, {"x"}, {"y"});
	for (const auto& colBase : t.columns_vec()) std::cout << "column " << colBase->name() << "\n";
	return 0;
}
