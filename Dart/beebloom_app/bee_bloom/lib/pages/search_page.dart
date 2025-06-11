import 'package:flutter/material.dart';
import '../constants/constants.dart';
import 'package:bee_bloom/data/pflanzendaten.dart';
import 'package:bee_bloom/data/pflanze.dart';
import 'package:bee_bloom/widgets/plantcard.dart';
import 'package:boxicons/boxicons.dart';

class SearchPage extends StatefulWidget {
  const SearchPage({super.key});

  @override
  State<SearchPage> createState() => _SearchPageState();
}

class _SearchPageState extends State<SearchPage> {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: MySearchPage(title: 'Suchen'),
      debugShowCheckedModeBanner: false,
    );
  }
}

class MySearchPage extends StatefulWidget {
  MySearchPage({required this.title});

  String title;

  @override
  State<StatefulWidget> createState() => _MySearchPageState();
}

class _MySearchPageState extends State<MySearchPage> {
  List<Pflanze> zumFiltern = List.generate(pflanzen.length, (int index) {
    return pflanzen[index].clone();
  });
  List<Plantcard> fuerErgebnisse = [];

  int aktuellerFilter = 0;

  final TextEditingController searchController = TextEditingController();

  void listerstellen(List<Plantcard> liste) {
    fuerErgebnisse.clear();
    for (int i = 0; i < zumFiltern.length; i++) {
      liste.add(Plantcard(
          title: zumFiltern[i].name, imageUrl: zumFiltern[i].bildpfad));
    }
  }

  void resetListeZumFiltern() {
    zumFiltern.clear();
    zumFiltern = List.generate(pflanzen.length, (int index) {
      return pflanzen[index].clone();
    });
  }

  void istTrockenheitsresistent() {
    if (aktuellerFilter == 1) {
      resetListeZumFiltern();
      zumFiltern
          .removeWhere((pflanze) => pflanze.trocken != "trockenheitsresistent");
      listerstellen(fuerErgebnisse);
      setState(() {});
    } else {
      resetListeZumFiltern();
      listerstellen(fuerErgebnisse);
      setState(() {});
    }
    print(fuerErgebnisse.length);
    print(aktuellerFilter);
  }

  void istSonnenresistent() {
    if (aktuellerFilter == 2) {
      resetListeZumFiltern();
      zumFiltern.removeWhere((pflanze) => pflanze.sonne != "volle Sonne");
      listerstellen(fuerErgebnisse);
      setState(() {});
    } else {
      resetListeZumFiltern();
      listerstellen(fuerErgebnisse);
      setState(() {});
    }
    print(fuerErgebnisse.length);
    print(aktuellerFilter);
  }

  void gutFuerArtenvielfalt() {
    if (aktuellerFilter == 3) {
      resetListeZumFiltern();
      zumFiltern.removeWhere(
          (pflanze) => pflanze.artenvielfalt != "gut für Artenvielfalt");
      listerstellen(fuerErgebnisse);
      setState(() {});
    } else {
      resetListeZumFiltern();
      listerstellen(fuerErgebnisse);
      setState(() {});
    }
    print(fuerErgebnisse.length);
    print(aktuellerFilter);
  }

  void initState() {
    super.initState();
    searchController.addListener(eingabeListener);
  }

  void dispose() {
    searchController.removeListener(eingabeListener);
    searchController.dispose();
    super.dispose();
  }

  eingabeListener() {
    suche(searchController.text);
  }

  void suche(String eingabe) {
    if (eingabe.isEmpty) {
      resetListeZumFiltern();
      listerstellen(fuerErgebnisse);
      aktuellerFilter = 0;
      setState(() {});
    } else {
      setState(() {
        aktuellerFilter = 0;
        resetListeZumFiltern();
        listerstellen(fuerErgebnisse);
        fuerErgebnisse.removeWhere((pflanze) =>
            !pflanze.title.toLowerCase().contains(eingabe.toLowerCase()));
      });
    }
  }

  Widget build(BuildContext context) {
    if (fuerErgebnisse.isEmpty) {
      listerstellen(fuerErgebnisse);
    }
    return Scaffold(
      body: Center(
        child: Container(
          color: white,
          child: Column(
            children: [
              Padding(
                padding: const EdgeInsets.fromLTRB(20, 15, 20, 0),
                child: SearchBar(
                  backgroundColor: MaterialStateProperty.all(lightgrey),
                  hintText: "Pflanzen suchen...",
                  controller: searchController,
                  padding: const MaterialStatePropertyAll<EdgeInsets>(
                    EdgeInsets.symmetric(horizontal: 16.0),
                  ),
                  leading: IconButton(
                    onPressed: () {},
                    icon: const Icon(
                      Icons.search,
                      color: green,
                    ),
                  ),
                ),
              ),
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  GestureDetector(
                    onTap: () {
                      if (aktuellerFilter != 1) {
                        aktuellerFilter = 1;
                      } else if (aktuellerFilter == 1) {
                        aktuellerFilter = 0;
                      }
                      istTrockenheitsresistent();
                    },
                    child: Padding(
                      padding:
                          const EdgeInsetsDirectional.fromSTEB(5, 15, 5, 15),
                      child: Container(
                        height: 30,
                        padding:
                            const EdgeInsetsDirectional.fromSTEB(40, 0, 40, 0),
                        decoration: BoxDecoration(
                          color: aktuellerFilter == 1 ? green : white,
                          borderRadius: BorderRadius.circular(30),
                          border: Border.all(
                            color: green,
                            width: 2,
                          ),
                        ),
                        child: Icon(
                          Boxicons.bx_droplet,
                          color: aktuellerFilter == 1 ? white : green,
                        ),
                      ),
                    ),
                  ),
                  GestureDetector(
                    onTap: () {
                      if (aktuellerFilter != 2) {
                        aktuellerFilter = 2;
                      } else if (aktuellerFilter == 2) {
                        aktuellerFilter = 0;
                      }
                      istSonnenresistent();
                    },
                    child: Padding(
                      padding:
                          const EdgeInsetsDirectional.fromSTEB(5, 15, 5, 15),
                      child: Container(
                        height: 30,
                        padding:
                            const EdgeInsetsDirectional.fromSTEB(40, 0, 40, 0),
                        decoration: BoxDecoration(
                          color: aktuellerFilter == 2 ? green : white,
                          borderRadius: BorderRadius.circular(50),
                          border: Border.all(
                            color: green,
                            width: 2,
                          ),
                        ),
                        child: Icon(
                          Boxicons.bx_sun,
                          color: aktuellerFilter == 2 ? white : green,
                        ),
                      ),
                    ),
                  ),
                  GestureDetector(
                    onTap: () {
                      if (aktuellerFilter != 3) {
                        aktuellerFilter = 3;
                      } else if (aktuellerFilter == 3) {
                        aktuellerFilter = 0;
                      }
                      gutFuerArtenvielfalt();
                    },
                    child: Padding(
                      padding:
                          const EdgeInsetsDirectional.fromSTEB(5, 15, 5, 15),
                      child: Container(
                        height: 30,
                        padding:
                            const EdgeInsetsDirectional.fromSTEB(40, 0, 40, 0),
                        decoration: BoxDecoration(
                          color: aktuellerFilter == 3 ? green : white,
                          borderRadius: BorderRadius.circular(50),
                          border: Border.all(
                            color: green,
                            width: 2,
                          ),
                        ),
                        child: Image(
                          image: AssetImage('images/bee.png'),
                          color: aktuellerFilter == 3 ? white : green,
                        ),
                      ),
                    ),
                  )
                ],
              ),
              Expanded(
                child: ListView.builder(
                  itemCount: fuerErgebnisse.length,
                  itemBuilder: (BuildContext context, int index) {
                    final element = fuerErgebnisse[index];
                    return fuerErgebnisse[index];
                  },
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
