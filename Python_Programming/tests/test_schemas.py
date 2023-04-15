from schema import schema_model, SchemaBaseModel
from schema.field import IntField, StringField, ListField,ObjectField

@schema_model
class Bar(object):
    bar = StringField(default="bar")
@schema_model
class Foo(object):
    foo = StringField(default="foo")
    bars = ObjectField(classobj=Bar,default="foo")

@schema_model
class Demo(object):
    age = IntField(default=0, required=True, min_value=10, max_value=20)
    name = StringField(default="test")
    foos = ObjectField(Foo)

@schema_model
class DemoList(object):
    ids = ListField(item_field=IntField)

    servers = ListField(item_field=StringField)

@schema_model
class DemoListObject(object):
    servers = ListField(item_field=Demo)

@schema_model
class DemoObject(object):
    age = IntField(default=0, required=True, min_value=10, max_value=20)
    server = ObjectField(classobj=Demo)

def test_validate():
    data = Demo(age=11)
    assert data.age >= 10 and data.age <= 20
    assert data.name == "test"

def test_list_validate():
    data = DemoList()
    assert data.ids == []
    data = DemoList(ids=[1,2,3])
    print(data.to_dict())
    assert data.ids == [1,2,3]

def test_list_object_validate():
    data = DemoListObject(servers=[{"age":20, "name": "demo"}])
    all =data.to_dict(only=["age"])
    # print(all['servers'])
    # for d in all['servers']:
    #     if hasattr(d, 'to_dict'):
    #         print(d.to_dict(),"......")
        # print("=====",d,"=====")

def test_object_validate():
    data = DemoObject(age=10,server={"age":20, "name": "demo"})
    # print(data.server.age)
    print(data.to_dict(only=[], remove=["age"]))

if __name__ == '__main__':
    # test_validate()
    # test_list_validate()
    test_list_object_validate()
    test_object_validate()

   
