use profile::FileContent;

#[derive(Copy, Clone, PartialEq, Eq, Debug)]
pub enum TokenType {
    Error,

    // whitespace/control
    StartOfInput,
    EndOfInput,
    EndOfLine,
    Indent,
    Outdent,

    // text
    Word,
    LineText,
    QuotedText,
    BlockText,

    // symbols
    Colon,
    GreaterThan,
}

#[derive(Debug)]
pub struct Token<'a> {
    pub token_type: TokenType,
    pub content: &'a FileContent,
    pub trivia_start: usize,
    pub text_start: usize,
    pub text_end: usize,
    pub value: Option<String>,
}

impl<'a> Token<'a> {
    pub fn trivia(&self) -> &'a str {
        &self.content.text()[self.trivia_start..self.text_start]
    }

    pub fn text(&self) -> &'a str {
        &self.content.text()[self.text_start..self.text_end]
    }

    pub fn value_or_text(&self) -> &str {
        match self.value {
            Some(ref value) => &value,
            None => self.text(),
        }
    }
}
