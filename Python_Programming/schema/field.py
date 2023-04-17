import re
from abc import ABCMeta,abstractmethod

class SchemaBaseModel(object):
    def __to_dict__(self, lst):
            rst = []
            for value in lst:
                if isinstance(value, list):
                    rst.append([self.__to_dict__(v) for v in value])
                elif isinstance(value, SchemaBaseModel):
                    rst.append(value.to_dict())
                else:
                    rst.append(value)
            return rst

    def to_dict(self,only=[],remove=[]):
        _dict = {}
        last_only = set(only).difference(set(remove))
        last_remove = set(remove).difference(set(only))
        for attr in self.__dict__:
            if last_only and not attr in last_only:
                continue
            if attr in last_remove:
                continue
            if not attr.startswith('_'):
                value = getattr(self, attr)
                if isinstance(value, list):
                    value = self.__to_dict__(value)
                elif isinstance(value, SchemaBaseModel):
                    value = value.to_dict()
                _dict[attr] = value
        return _dict

class Field():
    name = None
    default = None
    required = False
    __metaclass__ = ABCMeta
    def get_name(self):
        return self.name
    
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
    def __init__(self,name=None, default=0,required=False,min_value=None,max_value=None):
        self.default = default
        self.name = name
        self.required = required
        self.min_value = min_value
        self.max_value = max_value

    def validate(self, name, value):
        if not isinstance(value, int):
            raise ValueError("{} should be integer type".format(name))
        
        if self.min_value is not None and self.min_value > value:
            raise ValueError("{} should be larger than {}".format(name, self.min_value))
        
        if self.max_value is not None and self.max_value < value:
            raise ValueError("{} should be smaller than {}".format(name, self.max_value))
        
        return value
    
class FloatField(Field):
    def __init__(self,name=None, default=0.0,required=False,min_value=None,max_value=None):
        self.default = default
        self.name = name
        self.required = required
        self.min_value = min_value
        self.max_value = max_value

    def validate(self, name, value):
        if not isinstance(value, float):
            raise ValueError("{} should be float type".format(name))
        
        if self.min_value is not None and self.min_value > value:
            raise ValueError("{} should be larger than {}".format(name, self.min_value))
        
        if self.max_value is not None and self.max_value < value:
            raise ValueError("{} should be smaller than {}".format(name, self.max_value))
        
        return value
    
class BoolField(Field):
    def __init__(self,name=None, default=False, required=False):
        self.default = default
        self.name = name
        self.required = required

    def validate(self, name, value):
        if not isinstance(value, bool):
            raise ValueError("{} should be bool type".format(name))
        return value
    
class StringField(Field):
    def __init__(self,name=None, default='',required=False,min_length=None,max_length=None, regex=None):
        self.default = default
        self.name = name
        self.required = required
        self.min_length = min_length
        self.max_length = max_length
        self.regex = regex

    def validate(self, name, value):
        if not isinstance(value, (str,unicode)):
            raise ValueError("{} should be string type".format(name))
        
        length = len(value)
        if self.min_length is not None and self.min_length > length:
            raise ValueError("{} should be at least {} characters long".format(name, self.min_length))
        
        if self.max_length is not None and self.max_length < length:
            raise ValueError("{} maximum length should not exceed {} characters".format(name, self.max_length))
        
        if self.regex is not None:
            try:
                m = re.match(self.regex, value)
                if m is None or m.end() < len(value):
                    raise ValueError('{}: {} is NOT fully matched regex.'.format(name, self.regex))
            except re.error:
                raise ValueError('{}: {} is NOT a valid regex.'.format(name, self.regex))

        return value
    
class ListField(Field):
    def __init__(self,item_field,name=None, default=[],required=False,min_items=None,max_items=None):
        self.default = default
        self.name = name
        self.required = required
        self.min_items = min_items
        self.max_items = max_items
        self.item_field = item_field


    def validate(self, name, value):
        if not isinstance(value, list):
            raise ValueError("{} should be list type".format(name))
        
        if self.min_items is not None and len(value) < self.min_items:
            raise ValueError('{} should be at least {} items.'.format(name, self.min_items))

        if self.max_items is not None and len(value) > self.max_items:
            raise ValueError('{}\'s maximum length should not exceed {} characters.'.format(name, self.max_items))

        values = []
        for v in value:
            try:
                if isinstance(self.item_field, Field):
                    values.append(self.item_field.validate(name,v))
                elif issubclass(self.item_field, SchemaBaseModel):
                    values.append(self.item_field(**v))
                elif issubclass(self.item_field, Field):
                    values.append(self.item_field().validate(name, v))
                else:
                    raise ValueError("is {} unspport type.".format(name, type(v)))
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
        if isinstance(self.classobj, Field):
            return self.classobj.validate(name,value)
        elif issubclass(self.classobj, SchemaBaseModel):
            return self.classobj(**value)
        elif issubclass(self.classobj, Field):
            return self.classobj().validate(name,value)
        else:
            raise ValueError("{} should be <SchemaModel> or <Field> type".format(name))
        
