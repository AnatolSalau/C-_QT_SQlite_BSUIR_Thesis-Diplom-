// Получение ФИО клиента из отдельных полей
function client_CalcMainFIO(obj) {
  return obj.FamilyM+" "+obj.NameM+" "+obj.ParentM ;
}

// Получение ФИО ребенка из отдельных полей
function children_CalcMainFIO(obj) {
  return obj.Family+" "+obj.Name+" "+obj.Parent ;
}

// Вычисление возраста ребенка по дате рождения и текущей дате
function children_CalcAge(obj) {
  var tek = tools.nowDate() ;
  var bdate = tools.parseRusDate(obj.BDate) ;
  var age = tek.getFullYear()-bdate.getFullYear() ;
  bdate.setFullYear(tek.getFullYear()) ;
  if (bdate>tek) age-- ;
  if (age<1) age=1 ;
  return age ;
}

// Получение списка категорий клиента в столбец
function client_CalcCategories(obj) {
  var s = "" ;
  for (var k=0; k<obj.Categories.length; k++) {
      if (s!="") s+="\n" ;
      s+=obj.Categories[k] ;
  }
  return s ;
}

// Для отчета - вывода категорий через сепаратор
function client_CalcCategoriesSep(obj,sep) {
   var s = "" ;
  for (var k=0; k<obj.Categories.length; k++) {
      if (s!="") s+=sep ;
      s+=obj.Categories[k] ;
  }
  return s ;
}

// Для отчета - число детей у клиента
function client_CalcChildCount(obj) {
    if ("Childrens" in obj)
        return obj.Childrens.length;
    else
        return 0 ;
}

function emptyData(obj) {
    return '' ;
}
  
// Форматирование телефона
function client_FormatPhone(obj,format) {
  return tools.formatPhone(obj.PhoneM,format) ;
}

// Сортировка клиентов по умолчанию - город, потом фамилия
function client_lessThen(left,right) {
  if (left.City!=right.City) return left.City<right.City ;
  return left.FamilyM<right.FamilyM ;
}

// Сортировка детей по фамилии
function child_lessThen(left,right) {
  return left.Family<right.Family ;
}

// Сортировка клиента по числу детей
function childcount_lessThen(left,right) {
  return client_CalcChildCount(left)>client_CalcChildCount(right) ;
}

// Сортировка клиента по числу детей и фамилии
function childcountandfamily_lessThen(left,right) {
  if (client_CalcChildCount(left)!=client_CalcChildCount(right))
    return client_CalcChildCount(left)>client_CalcChildCount(right) ;
  else
    return left.FamilyM<right.FamilyM ;
}

// Фильтр по городу
function filter_City(obj,filter) {    
    return obj.City==filter.City ;
}

// Фильтр по категории
function filter_Cat(obj,filter) {
    for (var k=0; k<obj.Categories.length; k++)
        if (obj.Categories[k]==filter.Catname) return true ;
    return false ;
}

// Фильтр по числу детей
function filter_ChildCount(obj,filter) {
    return client_CalcChildCount(obj)>=filter.ChildCount ;
}

// Список городов для выпадающего списка
function getListCities() {
  var res = [] ;
  for (var i=0; i<list_cities.length; i++)
     res.push(list_cities[i].cityname) ;
  res.sort() ;
  return res ;
}
