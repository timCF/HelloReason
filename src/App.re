open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "appContainer":
        style([
          flex(1.0),
          backgroundColor(String("#F5F5F6")),
          marginTop(Pt(Platform.os() == Platform.Android ? 20.0 : 0.0)),
        ]),
      "title":
        style([
          fontSize(Float(19.)),
          fontWeight(`_600),
          textAlign(Center),
        ]),
    },
  );

let app = () =>
  <SafeAreaView style=styles##appContainer>
    <Text style=styles##title>
      {ReasonReact.string("Let's get this party started!!!")}
    </Text>
  </SafeAreaView>;
