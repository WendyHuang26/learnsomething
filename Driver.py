import cppimport.import_hook
import PricingUtil

util = PricingUtil.PricingUtil()
value = util.calcVal(100.0, 0.05, 2.0)
print(value)

if __name__ == "__main__":
    print("Nice work on creating the util! Make sure to check the unit tests!")
