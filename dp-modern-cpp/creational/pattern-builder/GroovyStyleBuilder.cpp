#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::ostringstream;
using std::pair;
using std::string;
using std::vector;

struct Tag {
    string name;
    string text;
    vector<Tag> children;
    vector<pair<string,string>> attributes;
    friend ostream& operator<<(ostream& os, const Tag& tag) {
        os << "<" << tag.name;
        for ( const auto & attr : tag.attributes ) {
            os << " " << attr.first << "=\"" << attr.second << "\"";
        }
        if ( tag.children.size() == 0 && tag.text.length() == 0 ) {
            // The case in which the tag is of the form <tag key="value" />
            os << "/>" << endl;
        } else {
            os << ">" << endl;
            // Append the text if any.
            if ( 0 < tag.text.length() ) {
                os << tag.text << endl;
            }
            for ( const auto & child : tag.children ) {
                os << child;
            }
            os << "</" << tag.name << ">";
        }
        return os;
    }
protected:
    // Hiding the constructors so as to be able to construct only specific tags.
    Tag(const string& name, const string& text) : name{name}, text{text} {}
    Tag(const string& name, const vector<Tag>& children) : name{name}, children{children} {}
};

struct P : public Tag {
    explicit P(const string& text) : Tag{"p",text} {}
    P(std::initializer_list<Tag> children) : Tag("p", children) {}
};

struct Img : public Tag {
    explicit Img(const string& url) : Tag{"img", ""} {
        attributes.emplace_back(pair{"src",url});
    }
};


int main(){
    cout << P { Img { "http://www.google.com" } } << endl;
//    Tag tag;
//    tag.name = "p";
//    cout << tag << endl;
    return EXIT_SUCCESS;
}
