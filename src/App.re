open BsReactNative;
open Proto_schema_pb;
open Proto_schema_types;

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

let bytes2js = bytes => {
  let byte_array = bytes |> Bytes.length |> Array.make(_, 0);
  bytes
  |> Bytes.iteri((index, char) => byte_array[index] = Char.code(char), _);
  byte_array
  |> Js.Typed_array.Uint8Array.make
  |> Js.Typed_array.Uint8Array.buffer;
};

let test_xhr = bytes => {
  let xhr = XmlHttpRequest.make();
  XmlHttpRequest.open_(
    xhr,
    ~method="POST",
    ~url="https://postman-echo.com/post",
    ~async=true,
    (),
  );
  XmlHttpRequest.setRequestHeader(xhr, "user-agent", "bs-xmlhttprequest");
  XmlHttpRequest.setRequestHeader(xhr, "Content-Type", "application/octet-stream");
  XmlHttpRequest.addEventListener(
    xhr,
    `load(
      _event => {
        let body = XmlHttpRequest.responseArrayBuffer(xhr);
        let status = XmlHttpRequest.status(xhr);
        Js.log2(status, body);
      },
    ),
  );
  /* can send bytes using XHR */
  bytes |> bytes2js |> XmlHttpRequest.sendArrayBuffer(xhr, _);
};

let app = () => {
  /* can encode and decode proto */
  let payment: payment = {amount: 100L, currency: Eur, reference: "123"};
  Js.log(payment);
  let encoder = Pbrt.Encoder.create();
  /* side-effects for stateful shit */
  encode_payment(payment, encoder);
  let encoded_payment = Pbrt.Encoder.to_bytes(encoder);
  Js.log(encoded_payment);
  let decoded_payment = encoded_payment->Pbrt.Decoder.of_bytes->decode_payment;
  Js.log(decoded_payment);
  Js.log(payment == decoded_payment);
  test_xhr(encoded_payment);
  /* can render something */
  <SafeAreaView style=styles##appContainer>
    <Text style=styles##title>
      {ReasonReact.string("Let's get this party started!!!")}
    </Text>
  </SafeAreaView>;
};
