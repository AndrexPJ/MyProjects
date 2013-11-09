type Atom = String
type Rule = (String,String)
--type Predicate (String,String,String)


rule ruleName atoms = map (\atomName -> (ruleName,atomName)) atoms




inPredicateProc name ruleNames rules = if length ruleNames == length (filter (\(_,atomName) -> atomName == name) rules)
				  	  then True
				          else False
predicate predName ruleNames rules = filter (\(_,name)-> inPredicateProc name ruleNames rules) $ question ruleNames [] rules  


question [] [] rules = rules
question ruleNames [] rules = concat $ map (\ruleName -> filter (\(_,ruleName',_)-> ruleName == ruleName')  rules ) ruleNames
question [] atomNames rules = concat $ map (\atomName -> filter (\(_,_,atomName')-> atomName == atomName')  rules ) atomNames
question ruleNames atomNames rules = question ruleNames [] $ question [] atomNames rules




--question ruleName rules = filter (\(_,ruleName',_) -> ruleName == ruleName') rules








