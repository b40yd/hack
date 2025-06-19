import importlib
import pkgutil
import logging

def auto_scan(package_name, prefix='', suffix=''):
    def decorator(cls):
        instances = {}
        def convert_class_name(name):
            return ''.join(s.capitalize() for s in name.split('_'))
        def scan_and_instantiate(package_path, package_prefix):
            package = importlib.import_module(package_path)
            for _, name, is_pkg in pkgutil.walk_packages(package.__path__, package_prefix):
                full_module_name = package_path + '.' + name if package_path else name
                try:
                    module = importlib.import_module(full_module_name)
                    # 检查模块中是否有符合命名规则的类
                    class_name = convert_class_name(name)
                    class_name = prefix + class_name + suffix
                    if hasattr(module, class_name):
                        klass = getattr(module, class_name)
                        if isinstance(klass, type):  # 确保是类
                            instances[name] = klass()  # 实例化
                except Exception as e:
                    logging.error("Error loading module %s: %s" % (full_module_name, str(e)))
                if is_pkg:
                    scan_and_instantiate(full_module_name, package_prefix)
        scan_and_instantiate(package_name, '')
        # 将实例字典附加到被装饰的类上
        cls.instances = instances
        return cls
    return decorator

@auto_scan('services.options', suffix='FilterOption')
class FilterOptionFactory(object):
    instances = {}
    def get_filter_option_instance(self, name, **config):
        instance = self.instances.get(name, None)
        if instance:
            instance.config(**config)
        return instance
