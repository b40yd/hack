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
        def __init__(self, params={} ,**kwags):
            required_diff = []
            if params and not isinstance(params, dict):
                raise ValueError("params should be <class 'dict'>.")
            for field_name, field_type in validate_props.items():
                value = kwags.get(field_name, None)
                _value = params.get(field_name, None)
                value = _value if value is None else value
                if value is not None:
                    if field_name in required_props:
                        required_diff.append(field_name)
                    self.__dict__[field_name] = field_type.validate("<{}.{}>".format(cls.__name__,field_name),value)
                else:
                    self.__dict__[field_name] = field_type.get_default()
                    
            for field_name in set(required_props.keys()).difference(set(required_diff)):
                validate_props[field_name].required_missing(field_name)
                

        def __getattr__(self, item):
            if item in self.__dict__:
                return self.__dict__[item]
            else:
                raise AttributeError("No such attribute: {}".format(item))
            
        def __setattr__(self, name, value):
            if not name in self.__dict__:
                raise AttributeError("No such attribute: {}".format(name))
            validator = validate_props.get(name, None)
            if validator:
                self.__dict__[name] = validator.validate(name, value)
        
        def __getitem__(self, item):
            if item in self.__dict__:
                return self.__dict__[item]
        
        def __str__(self):
            return self.__name__
        
        def __repr__(self):
            return "<{}.{}>".format(__name__,self.__name__)
        
    return SchemaModel
