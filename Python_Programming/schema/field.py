from abc import ABCMeta,abstractmethod

class SchemaBaseModel(object):
    pass

UNLIMITED = -1
class Field():
    name = None
    default = None
    required = False
    __metaclass__ = ABCMeta
    def get_default(self):
        return self.default
    
    def required_missing(self, name):
        raise ValueError("{} should be required".format(name))

    def get_required(self):
        return self.required
    
    @abstractmethod
    def validate(self, name, value):
        pass

class IntField(Field):
    def __init__(self,name=None, default=0,required=False,min_value=UNLIMITED,max_value=UNLIMITED):
        self.default = default
        self.name = name
        self.required = required
        self.min_value = min_value
        self.max_value = max_value

    def validate(self, name, value):
        if not isinstance(value, int):
            raise ValueError("{} should be integer type".format(name))
        
        if self.min_value > UNLIMITED and self.min_value > value:
            raise ValueError("{} should be larger than {}".format(name, self.min_value))
        
        if self.max_value > UNLIMITED and self.max_value < value:
            raise ValueError("{} should be smaller than {}".format(name, self.max_value))
        
        return value
    
class FloatField(Field):
    def __init__(self,name=None, default=0.0,required=False,min_value=UNLIMITED,max_value=UNLIMITED):
        self.default = default
        self.name = name
        self.required = required
        self.min_value = min_value
        self.max_value = max_value

    def validate(self, name, value):
        if not isinstance(value, float):
            raise ValueError("{} should be float type".format(name))
        
        if self.min_value > UNLIMITED and self.min_value > value:
            raise ValueError("{} should be larger than {}".format(name, self.min_value))
        
        if self.max_value > UNLIMITED and self.max_value < value:
            raise ValueError("{} should be smaller than {}".format(name, self.max_value))
        
        return value
    
class BoolField(Field):
    def __init__(self,name=None, default=False,required=False,min_value=UNLIMITED,max_value=UNLIMITED):
        self.default = default
        self.name = name
        self.required = required

    def validate(self, name, value):
        if not isinstance(value, bool):
            raise ValueError("{} should be bool type".format(name))
        return value
    
class StringField(Field):
    def __init__(self,name=None, default=0.0,required=False,min_length=UNLIMITED,max_length=UNLIMITED):
        self.default = default
        self.name = name
        self.required = required
        self.min_length = min_length
        self.max_length = max_length

    def validate(self, name, value):
        if not isinstance(value, str):
            raise ValueError("{} should be string type".format(name))
        
        if self.min_length > UNLIMITED and self.min_length > value:
            raise ValueError("{} should be at least {} characters long".format(name, self.min_length))
        
        if self.max_length > UNLIMITED and self.max_length < value:
            raise ValueError("{} maximum length should not exceed {} characters".format(name, self.max_length))
        
        return value
    
class ListField(Field):
    def __init__(self,item_field,name=None, default=[],required=False,min_items=UNLIMITED,max_items=UNLIMITED):
        self.default = default
        self.name = name
        self.required = required
        self.min_items = min_items
        self.max_items = max_items
        self.item_field = item_field


    def validate(self, name, value):
        if not isinstance(value, list):
            raise ValueError("{} should be list type".format(name))
        
        if self.min_items > UNLIMITED and len(value) < self.min_items:
            raise ValueError('{} should be at least {} items.'.format(name, self.min_items))

        if self.max_items > UNLIMITED and len(value) > self.max_items:
            raise ValueError('{}\'s maximum length should not exceed {} characters.'.format(name, self.max_items))
        
        if  isinstance(self.item_field, Field):
            raise ValueError("{} item should be Field type".format(name))
        
        values = []
        for v in value:
            try:
                if issubclass(self.item_field, SchemaBaseModel):
                    values.append(self.item_field(**v))
                else:
                    values.append(self.item_field().validate("", v))
            except ValueError as e:
               raise ValueError("The {} list {}".format(name, e))
        
        return values

class ObjectField(Field):
    def __init__(self,classobj,name=None, default={},required=False):
        self.default = default
        self.name = name
        self.required = required
        self.classobj = classobj

    def validate(self, name, value):
        if not issubclass(self.classobj, SchemaBaseModel):
            raise ValueError("{} should be <SchemaModel> type".format(name))
        
        return self.classobj(**value)
