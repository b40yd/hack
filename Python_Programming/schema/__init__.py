from .field import SchemaBaseModel

def schema_model(cls):
    if not isinstance(cls, type):
        raise ValueError("{} is not object.".format(cls.__name__))

    validate_props = {}
    required_props = {}
    for field_name, field_type in vars(cls).items():
        if not field_name.startswith('__'):
            alisa_name =  field_type.get_name()
            if alisa_name:
                field_name = alisa_name
            if field_type.get_required():
                required_props[field_name] = field_type.get_required()
            validate_props[field_name] = field_type
    
    class SchemaModel(SchemaBaseModel):
        __doc__ = cls.__doc__
        __name__ = cls.__name__
        __module__ = cls.__module__
        def __init__(self, **kwags):
            for field_name, field_type in validate_props.items():
                value = kwags.get(field_name, None)
                if value:
                    if field_name in required_props:
                        required_props.pop(field_name)
                    self.__dict__[field_name] = field_type.validate("<{}.{}>".format(cls.__name__,field_name),value)
                else:
                    self.__dict__[field_name] = field_type.get_default()
                    
            for field_name in required_props.keys():
                validate_props[field_name].required_missing(field_name)
                

        def __getattr__(self, item):
            if item in self.__dict__:
                return self.__dict__[item]
            else:
                raise AttributeError("No such attribute: %s" % item)
            
        def __setattr__(self, name, value):
            self.__dict__[name] = value
            return value
        
        def __getitem__(self, item):
            if item in self.__dict__:
                return self.__dict__[item]
        
        def __str__(self):
            return self.__name__
        
        def __repr__(self):
            return "<{}.{}>".format(__name__,self.__name__)
        
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
        
    return SchemaModel
